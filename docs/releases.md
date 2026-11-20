# Releases

Releases are published on this repository's
[GitHub Releases page](https://github.com/haiven-dev/haiven-sdk-unreal/releases).
This repository is published from Haiven's SDK source, and Haiven's release
pipeline builds and publishes every release from that source after a
maintainer review. Nothing in this repository cuts a release: there is no
release workflow, release pull request, or tag to push here.

## Assets

Each release carries:

- `haiven-unreal-plugin-source-<version>.zip` — the plugin source. Its only
  top-level entry is `Haiven/`, for `<Project>/Plugins/`. It leaves out
  `Binaries`, `Intermediate`, `Saved`, and `DerivedDataCache`; the project
  that installs it compiles it.
- `SHA256SUMS` — the SHA-256 digest of every asset, in `sha256sum` format.
  Check a download with `sha256sum -c SHA256SUMS`.

The release notes list each asset with its digest and name the source
commit it was built from. Releases do not attach prebuilt plugin binaries.
The engines the plugin is tested on are in
[engine-versions.md](engine-versions.md).

## Versions

Versions follow [Semantic Versioning](https://semver.org/). A release is
tagged `v<version>`, and `VersionName` in the released plugin's
`Haiven.uplugin` carries the same number; the pipeline refuses to publish a
release whose `VersionName` differs from its tag. `0.0.0` is the
development placeholder and is never released. Haiven's SDK and demo
repositories share one version line: the repositories in one release carry
the same version, and a release can cover only some of them, so this
repository's version numbers can skip. A version with a pre-release suffix
(`v1.2.3-rc.1`) is published as a GitHub pre-release and is never marked
Latest. Leave `VersionName` to Haiven's
release process; a pull request here does not choose a version.

## Contributing

Source updates arrive as pull requests into `main`. Contributions are
welcome as pull requests here too; see [CONTRIBUTING.md](../CONTRIBUTING.md).
Haiven's maintainers carry each accepted change into Haiven's source, so
later updates keep it.
