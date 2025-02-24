set(VSCODE_DIR "/workspaces/.vscode")

string(CONFIGURE "${VSCODE_LAUNCH_COMMANDS}" VSCODE_LAUNCH_COMMANDS)

configure_file("${VSCODE_DIR}/launch.json.in" "${VSCODE_DIR}/launch.json")
message("Generated VS Code launch.json at: ${VSCODE_DIR}/launch.json")
