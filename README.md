# git-util
Utilities for Git

## install
Add the following lines in your bash profile (e.g., `~/.bashrc`)
`
export GITUTIL_DIR="/directory/to/this/repository" # Change this path !
export PATH="${GITUTIL_DIR}":$PATH
source "${GITUTIL_DIR}/.git-util_aliases"
source "${GITUTIL_DIR}/.git-util_completion"
`
