# Development

## Checks without Unreal

From the repository root, with no Unreal install:

```sh
./verify.sh
node validate-plugin.mjs
```

`verify.sh` builds `protocol_test.cpp` as C++17 with `-Wall -Wextra
-Werror` and runs it. That covers the protocol and session headers only.
If neither `g++` nor `clang++` is on `PATH`, the script prints
`skipping C++: no g++ or clang++` and exits 0. That skip is not a passing
protocol run.

`node validate-plugin.mjs` checks the plugin descriptor and the build
rules. It does not load the plugin in an editor.

## Engine automation

The editor tests run from `host/`, an Unreal project that enables the plugin.
This repository has no runner script for them. With an entitled Linux engine
whose root directory contains `Engine/`, stage a copy of the host with the
plugin inside it, then build and run it:

```sh
ENGINE_ROOT=/path/to/UE_5.8.2        # the directory that contains Engine/
STAGE="$PWD/build/unreal-host"
rm -rf "$STAGE" && mkdir -p "$STAGE/Plugins"
cp -R host/. "$STAGE/"
cp -R Haiven "$STAGE/Plugins/Haiven"
mkdir -p "$STAGE/Content/HaivenTestFixtures"
cp conformance/gaming-client/v0/generated/suite.json \
  "$STAGE/Content/HaivenTestFixtures/gaming-client-v0.json"
# Set "EngineAssociation" in "$STAGE/HaivenTests.uproject" to "5.8" (or "5.6").
"$ENGINE_ROOT/Engine/Build/BatchFiles/Linux/Build.sh" \
  HaivenTestsEditor Linux Development "$STAGE/HaivenTests.uproject" -WaitMutex
"$ENGINE_ROOT/Engine/Binaries/Linux/UnrealEditor-Cmd" "$STAGE/HaivenTests.uproject" \
  -unattended -NullRHI -nosplash -nosound -stdout \
  "-ExecCmds=Automation RunTest Haiven.;Quit"
```

The `Haiven.Conformance.Client` test reads the staged
`Content/HaivenTestFixtures/gaming-client-v0.json` and fails without it.
Build with the clang toolchain bundled with the engine, not the system
compiler. The queued `Quit` exits with the automation result once the
`Haiven.` tests finish. Those editor tests do not open a live HTTP or
WebSocket fixture. What the cases cover is in
[host/README.md](../host/README.md).

How one source tree builds on several engines is in
[engine-versions.md](engine-versions.md).

## Conformance

`conformance_test.cpp` drives `Haiven::FSessionCore` against the suite
at `conformance/gaming-client/v0/generated/suite.json`. It is not part
of `verify.sh`. It prints a skip and exits 0 unless
`HAIVEN_CONFORMANCE_SUITE` (that file's path),
`HAIVEN_FIXTURE_BASE_URL`, and `HAIVEN_FIXTURE_WS_URL` are set.
