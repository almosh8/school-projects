set -e

git checkout -b develop || true
git push --set-upstream origin develop || true

cp ../materials/linters/.clang-format . || true