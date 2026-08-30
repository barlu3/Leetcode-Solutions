import argparse
import os
import re
import shutil

# LeetHub drops each new problem as a top-level folder in the repo root.
# This script files those loose folders into LeetCode/<Difficulty>/.
LEETCODE_DIR = "LeetCode"
DIFFICULTIES = ["Easy", "Medium", "Hard"]

# LeetHub's README always states the difficulty in its own heading,
# e.g. "<h2><a ...>1. Two Sum</a></h2><h3>Easy</h3>". Anchoring on that
# tag avoids false hits on words like "Hard" appearing in problem prose.
DIFFICULTY_TAG = re.compile(r"<h3>\s*(Easy|Medium|Hard)\s*</h3>", re.IGNORECASE)


def detect_difficulty(readme_path):
    """Return the problem's difficulty, or None if it can't be determined."""
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()

    match = DIFFICULTY_TAG.search(content)
    if match:
        return match.group(1).capitalize()

    # Fall back to a loose scan for READMEs that don't use the heading format.
    found = [d for d in DIFFICULTIES if d in content]
    if len(found) == 1:
        return found[0]
    return None


def find_loose_problems(repo_path):
    """Yield (name, path) for every problem folder sitting outside LeetCode/."""
    for item in sorted(os.listdir(repo_path)):
        item_path = os.path.join(repo_path, item)
        if not os.path.isdir(item_path):
            continue
        if item.startswith('.') or item == LEETCODE_DIR:
            continue
        # A problem folder is identified by its README; anything else at the
        # root (docs, tooling, etc.) is left alone.
        if os.path.exists(os.path.join(item_path, "README.md")):
            yield item, item_path


def organize_leethub_repo(repo_path=".", dry_run=False):
    leetcode_path = os.path.join(repo_path, LEETCODE_DIR)
    moved = skipped = 0

    for name, src_path in find_loose_problems(repo_path):
        try:
            difficulty = detect_difficulty(os.path.join(src_path, "README.md"))
        except OSError as e:
            print(f"Error reading {name}: {e}")
            skipped += 1
            continue

        if not difficulty:
            print(f"Skipped (no difficulty found): {name}")
            skipped += 1
            continue

        dest_dir = os.path.join(leetcode_path, difficulty)
        dest_path = os.path.join(dest_dir, name)

        if os.path.exists(dest_path):
            print(f"Skipped (already in {LEETCODE_DIR}/{difficulty}/): {name}")
            skipped += 1
            continue

        if dry_run:
            print(f"Would move: {name} -> {LEETCODE_DIR}/{difficulty}/")
        else:
            os.makedirs(dest_dir, exist_ok=True)
            shutil.move(src_path, dest_path)
            print(f"Moved: {name} -> {LEETCODE_DIR}/{difficulty}/")
        moved += 1

    print(f"\n{moved} moved, {skipped} skipped.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=f"File loose LeetHub problem folders into {LEETCODE_DIR}/<Difficulty>/.")
    parser.add_argument("repo_path", nargs="?", default=".",
                        help="Repository root (default: current directory)")
    parser.add_argument("--dry-run", action="store_true",
                        help="Show what would move without touching the filesystem")
    args = parser.parse_args()
    organize_leethub_repo(args.repo_path, args.dry_run)
