set -e

git checkout -b develop || true
git checkout develop || true
git push --set-upstream origin develop || true
git pull origin develop || true

cp ../materials/linters/.clang-format . || true
