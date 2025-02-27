"""
Source Collector for CMakeList.txt files.

Updates or generates a valid CMakeList.txt output.
"""

import argparse
import os
import re
from pathlib import Path

from typing import List

file_types = ["*.cpp", "*.h"]

cmake_app_path = Path("../../src/CMakeLists.txt")
source_app_path = Path("../../src")

cmake_testapp_path = Path("../../tests/CMakeLists.txt")
source_testapp_path = Path("../../tests")


def collect_sources(path: Path, patterns=None):
    """
    Collect source files from path with expected file_ext

    :param path: root path where source files are collected
    :param patterns: the filters which must match for source collection
    :return: a list of all source files
    """
    files = []
    if patterns is None:
        patterns = file_types

    for pattern in patterns:
        files.extend(list(path.rglob(pattern)))

    return files


def replace_cmake_paths(files: List[Path], cmake_file: Path, target_name: str):
    """
    Replaces files in CMakeList.txt compatible output

    :param files: paths to print relative to cmake_file
    :param cmake_file: path to CMakeList.txt file
    :param target_name: the Target name to replace given files
    """
    # output
    with open(cmake_file, "r", encoding="UTF-8") as file:
        content = file.read()

    def replace(command, target):
        name = target.replace('\\', '')
        include_list = f"{command}({name}" + "\n" + __converter_to_string(files, cmake_file) + "\n)"
        regex = command + r"\(" + re.escape(target) + r"([^)]*)\)"
        match = re.search(regex, content, re.MULTILINE)

        if match is not None:
            return content.replace(match.group(0), include_list)
        return content

    content = replace("add_library", target_name)
    content = replace("add_executable", target_name)

    with open(cmake_file, "w", encoding="UTF-8") as file:
        file.write(content)

    print(f"CMakeList '{cmake_file.resolve()}' updated ")

def print_cmake_paths(files: List[Path], cmake_file: Path):
    """
    Prints files in CMakeList.txt compatible output

    :param files: paths to print relative to cmake_file
    :param cmake_file: path to CMakeList.txt file
    """
    print(f"Content for {cmake_file.resolve()}")
    print("======================")
    print(__converter_to_string(files, cmake_file))


def __converter_to_string(files: List[Path], cmake_file: Path) -> str:
    cmake_folder_path = cmake_file.parent.absolute().resolve()

    result_grouped = {}
    result = ""

    # create groups
    for file in sorted(files, key=lambda i: i.stem):
        file_path = file.absolute().resolve()

        relative_path = Path(os.path.relpath(file_path, cmake_folder_path))

        # group result
        group_name = relative_path.parent.name
        if group_name not in result_grouped:
            result_grouped[group_name] = []
        result_grouped[group_name].append(relative_path)

    for group_name in result_grouped:
        paths = result_grouped[group_name]

        result += f"    # {group_name}" + "\n"
        for path in paths:
            result += f"    " + str(path).replace('\\', '/')
            result += "\n"
        result += "\n"

    return result.rstrip()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', '--directory', default=source_app_path)
    parser.add_argument('-c', '--cmake-file', default=cmake_app_path)
    parser.add_argument('-t', '--target-name', default=None)

    args = parser.parse_args()

    directory_path = Path(args.directory)
    cmake_file_path = Path(args.cmake_file)
    target_name = args.target_name

    # set work folder to current script file
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    os.chdir(dname)

    print(__doc__)

    source_files = collect_sources(directory_path)

    if target_name is None:
        print_cmake_paths(source_files, cmake_file_path)
    else:
        replace_cmake_paths(source_files, cmake_file_path, target_name)
