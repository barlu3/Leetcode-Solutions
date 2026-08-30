import argparse
import os
import re
import shutil
import subprocess

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


ROOT_README = "README.md"

# LeetHub appends one table row per problem/topic, pointing at wherever the
# folder sat when it was committed:
#   | [0001-two-sum](https://github.com/<user>/<repo>/tree/master/0001-two-sum) |
# After a move those links are stale, so rows get rewritten from what is
# actually on disk. The link target and trailing cells are rebuilt from
# scratch, so only the row prefix, slug, and repo URL base are captured.
README_ROW = re.compile(
    r"^(?P<prefix>\|\s*\[)(?P<slug>[^\]]+)\]\("
    r"(?P<base>https://github\.com/[^/]+/[^/]+)/tree/[^/)]+/[^)]*\).*$"
)


def current_branch(repo_path):
    """Branch name to use in README links; falls back to 'main'."""
    try:
        result = subprocess.run(
            ["git", "-C", repo_path, "symbolic-ref", "--short", "HEAD"],
            capture_output=True, text=True, timeout=10)
        if result.returncode == 0 and result.stdout.strip():
            return result.stdout.strip()
    except (OSError, subprocess.SubprocessError):
        pass
    return "main"


def index_problems(repo_path):
    """Map each problem slug to the difficulty folder it currently lives in."""
    located = {}
    leetcode_path = os.path.join(repo_path, LEETCODE_DIR)
    for difficulty in DIFFICULTIES:
        difficulty_path = os.path.join(leetcode_path, difficulty)
        if not os.path.isdir(difficulty_path):
            continue
        for slug in os.listdir(difficulty_path):
            if os.path.isdir(os.path.join(difficulty_path, slug)):
                located[slug] = difficulty
    return located


def update_root_readme(repo_path, dry_run=False):
    """Repoint root README rows at each problem's real location."""
    readme_path = os.path.join(repo_path, ROOT_README)
    if not os.path.exists(readme_path):
        print(f"No {ROOT_README} at repo root; skipping link update.")
        return

    located = index_problems(repo_path)
    branch = current_branch(repo_path)

    with open(readme_path, 'r', encoding='utf-8') as f:
        lines = f.read().splitlines(keepends=True)

    changed = 0
    unknown = set()
    for i, line in enumerate(lines):
        match = README_ROW.match(line.rstrip("\n"))
        if not match:
            continue

        slug = match.group("slug")
        difficulty = located.get(slug)
        if not difficulty:
            unknown.add(slug)
            continue

        newline = "\n" if line.endswith("\n") else ""
        target = f"{LEETCODE_DIR}/{difficulty}/{slug}/"
        # Rebuild the trailing cells so the difficulty column is always
        # present and correct, even on rows LeetHub wrote without one.
        rebuilt = (f"{match.group('prefix')}{slug}]({match.group('base')}"
                   f"/tree/{branch}/{target}) | {difficulty} |{newline}")

        if rebuilt != line:
            lines[i] = rebuilt
            changed += 1

    for slug in sorted(unknown):
        print(f"README row left as-is (problem not found on disk): {slug}")

    if not changed:
        print(f"{ROOT_README} already up to date.")
        return

    if dry_run:
        print(f"Would update {changed} link(s) in {ROOT_README}.")
    else:
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.writelines(lines)
        print(f"Updated {changed} link(s) in {ROOT_README}.")


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

    update_root_readme(repo_path, dry_run)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=f"File loose LeetHub problem folders into {LEETCODE_DIR}/<Difficulty>/.")
    parser.add_argument("repo_path", nargs="?", default=".",
                        help="Repository root (default: current directory)")
    parser.add_argument("--dry-run", action="store_true",
                        help="Show what would move without touching the filesystem")
    args = parser.parse_args()
    organize_leethub_repo(args.repo_path, args.dry_run)
