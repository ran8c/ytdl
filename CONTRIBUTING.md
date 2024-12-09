# Merge Checklist

- [ ] Fix any `clang-tidy` warnings (`cmake --build build/debug > build.log`)
- [ ] Format all C++ files (`fd . src include -e cpp -e hpp -x clang-format -i`)
- [ ] Format all CMakeLists files (`fd 'CMakeLists.txt' -x cmake-format -i`)
- [ ] Rebase your `feat` branch onto `main` and fix any conflicts (`git rebase main`)
- [ ] Rebase your `feat` branch to squash and rewords your commits (`git rebase -i main`)
  - Try to organize your changes into a set of atomic commits (a small commit that only affects one thing)
    - This is subjective, but try to make it "look" like the commits already on `main`
  - Be informative: subject should clearly explain *what* the change is, body should explain *why* the change was made (if needed)
    - Subjects are 50 characters long, body text is wrapped at 72 characters
- [ ] Finish by writing a Pull Request with your changes
