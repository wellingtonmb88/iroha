# Contributing guidelines

:star::tada: First off, thanks for taking the time to contribute! :tada::star:

The following is a short set of guidelines for contributing to Iroha. 



#### Table Of Contents

##### [How Can I Contribute?](#how-can-i-contribute-1)

- [Reporting bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Asking Question](#asking-question)
- [Your First Code Contribution](#your-first-code-contribution)
- [Pull Requests](#pull-requests)

##### [Styleguides](#styleguides-1)

- [Git Commit Messages](#git-commit-messages)
- [C++ StyleGuide](#C++-styleguide)
- [Documentation Styleguide](#documentation-styleguide)

##### [Additional Notes](#additional-notes)

- [Issue and Pull Request Labels](#issue-and-pull-request-labels)
- [Contact Developers](#contact-developers)



## How Can I Contribute?

### Reporting bugs

*Bug* is an error, design flaw, failure or fault in Iroha that causes it to produce an incorrect or unexpected result, or to behave in unintended ways. 

Bugs are tracked as [GitHub Issues](https://guides.github.com/features/issues/). To submit a bug, create new Issue and include these details:
- **Title**
    - Write prefix `[Bug]` for the title
    - Use a clear and descriptive title
- **Body** - include the following sections:
    - Steps to reproduce
    - Expected behavior
    - Actual behavior



### Suggesting Enhancements

An *enhancement* is a code or idea, which makes **existing code or design** faster, more stable, portable, secure or better in any other way.

Enhancements are tracked as [GitHub Issues](https://guides.github.com/features/issues/). To submit new enhancement, create new Issue and incllude these details:

- **Title**
    - Write prefix `[Enhancement]`
    - Use a clear and descriptive title
- **Body** - include the following sections:
    - *Motivation* - why do we need it?
    - *Target* - what is going to be improved?
    - *Description* - how to implement it?



### Asking Questions

A *question* is any discussion that is typically neigher a bug, nor feature requests, nor improvements - "How do I do X?".

Questions are tracked as [Github Issues](https://guides.github.com/features/issues/) or via private messages in [your favourite messenger](#contact-developers).

To submit new question in GitHub Issues, it must include these details:

- **Title**
    - Write prefix `[Question]`
    - Use a clear and descriptive title
- **Body** - describe your question with as many details as possible.



### Your First Code Contribution

Read our [C++ Style Guide](#c++-style-guide) and start with beginner-friendly issues with label [`[good-first-issue]`](https://github.com/hyperledger/iroha/issues?q=is:open+is:issue+label:good-first-issue ). 



### Pull Requests

- Fill in [the required template](.github/PULL_REQUEST_TEMPLATE.md)

- **Write tests** for new code.

- Every pull request should be reviewed and **get at least two approvals**.

- Do not include issue numbers in the PR title or commit messages.

- Include issue numbers in Pull Request body only.

- When finished work, **rebase onto base branch** with 
    ```bash
    $ git fetch
    $ git rebase -i <base-branch>
    ```

    [Step-by-step guide](https://soramitsu.atlassian.net/wiki/spaces/IS/pages/11173889/Rebase+and+merge+guide).

- Follow the [C++ Style Guide](#C++-style-guide).

- Follow the [Git Style Guide](#git-commit-messages) .

- **Document new code** based on the [Documentation Styleguide](#documentation-styleguide)

- End all files with a newline.




## Styleguides

### Git Style Guide

- **Use present tense** ("Add feautre", not "Added feature").
- **Use imperative mood** ("Deploy docker to..." not "Deploys docker to...").
- Write meaningful commit message.
- **Sign every commit** with [DCO](https://github.com/apps/dco): `Signed-off-by: $NAME <$EMAIL>`. 
    You can do it automatically using `git commit -s`.
- Do not include PR or Issue number in commit message. 
- Limit the first line of commit message to 50 characters or less.
- When only changing documentation, include `[ci skip]` in the commit description.
- We use mixed approach of [Github Flow](https://guides.github.com/introduction/flow/) and [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/). More at [Iroha Working Agreement](https://github.com/hyperledger/iroha/wiki/Iroha-working-agreement#2-version-control-system).




### C++ Style Guide

- Use [clang-format](http://clang.llvm.org/docs/ClangFormat.html) for code formatting. 
- Follow [CppCoreGuidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) and [Cpp Best Practices](https://lefticus.gitbooks.io/cpp-best-practices).
- Avoid platform-dependent code.
- Use [C++14](https://en.wikipedia.org/wiki/C%2B%2B14).
- Use [camelCase](https://en.wikipedia.org/wiki/Camel_case).



### Documentation Styleguide

- Use [Doxygen](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html).
- Document all public API: methods, functions, members, templates, classes...



## Additional Notes

### Issue and Pull Request Labels

Labels help us to track and manage issues and pull requests.

| Label Name              | Description                              |
| :---------------------- | ---------------------------------------- |
| `enhancement`           | Any improvements in existing code, fresh ideas. |
| `bug`                   | Bugs or reports that are very likely to be bugs. |
| `question`              | Questions more than bug reports or feature requests - "How do I do X" |
| `feature`               | Feature requests.                        |
| `good-first-issue`      | Good starting point to begin contributing. |
| `help-wanted`           | Maintainers ask for help to work on this issue. |
| `needs-reproduction`    | Issue is likely a bug, but needs to be reproduced and confirmed. |
| `accepted`              | Pull request is accepted and can be merged. |
| `candidate-for-closing` | Outdated Issue/Pull Request and is candidate for closing. |
| `challeging-task`       | Small but hard task.                     |
| `needs-correction`      | Pull request or Issue that should be corrected by opener. |
| `needs-review`          | Pull request or Issue that should be reviewed by maintainer. |
| `pri:low`               | Low priority.                            |
| `pri:normal`            | Normal priority.                         |
| `pri:important`         | Important issue.                         |
| `pri:critical`          | Critical issue. Must be fixed immediately. |
| `pri:blocker`           | Issue blocked on other issues.           |
| `status:in-progress`    | Work in progress.                        |
| `status:inactive`       | Inactive PR or Issue. Likely to become a `candidate-for-closing` |
| `status:pending`        | Issue is posted, but is not reviewed by maintainers. |
| `status:resolved`       | Resolved issue.                          |
| `status:wontfix`        | Core team has decided not to fix these issue for now. |



### Contact Developers

Developers are available at:

| Service      | Link                                     |
| ------------ | ---------------------------------------- |
| RocketChat   | https://chat.hyperledger.org/channel/iroha |
| Mailing List | [hyperledger-iroha@lists.hyperledger.org](mailto:hyperledger-iroha@lists.hyperledger.org) |
| Gitter       | https://gitter.im/hyperledger-iroha/Lobby |
| Telegram     | https://t.me/joinchat/Al-9jkCZ6eePL9JMQtoOJw |



---

Thank you for reading whole document! 

Your code phrase is "I promise to follow Contributing Guidelines."* without quotes.

*Note: this code phrase is used by GitIssueBot to ensure that first time contributors at least scrolled down to find it.