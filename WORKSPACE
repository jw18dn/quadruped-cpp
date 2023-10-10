workspace(name = "quadruped")

# Load Bazel Rules to create a bazel build for a git repo without bazel support:
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

# Eigen:
new_git_repository(
    name = "eigen",
    remote = "https://gitlab.com/libeigen/eigen.git",
    commit = "3147391d946bb4b6c68edd901f2add6ac1f31f8c",
    build_file = "//third_party/eigen:BUILD.bazel",
)