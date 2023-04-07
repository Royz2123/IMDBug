from typing import Any, Dict, List

from tree_sitter import Language, Parser

Language.build_library(
    # Store the library in the `build` directory
    "build/my-languages.so",
    # Include one or more languages
    ["file_to_funcs/tree-sitter-c"],
)

Language.build_library(
    # Store the library in the `build` directory
    "build/my-languages-cpp.so",
    # Include one or more languages
    ["file_to_funcs/tree-sitter-cpp"],
)

C_LANGUAGE = Language("build/my-languages.so", "c")
CPP_LANGUAGE = Language("build/my-languages-cpp.so", "cpp")

cpp_parser = Parser()
cpp_parser.set_language(CPP_LANGUAGE)

c_parser = Parser()
c_parser.set_language(C_LANGUAGE)

FUNC_NODE_TYPES = ["function_definition", "preproc_function_def"]


def convert_file_to_funcs(
    source_code: str, tree_type: str = "cpp"
) -> List[Dict[str, Any]]:
    lines = source_code.splitlines(True)

    if tree_type == "c":
        tree = c_parser.parse(bytes(source_code, "utf-8"))
    elif tree_type in ["cpp", "h", "hpp", "h++", "c++", "cc", "hh"]:
        tree = cpp_parser.parse(bytes(source_code, "utf-8"))
    else:
        raise Exception(f"Invalid tree type for parsing: {tree_type}")

    func_nodes = []
    for node in tree.root_node.children:
        if node.type in FUNC_NODE_TYPES:
            func_nodes.append(node)
        for node_1 in node.children:
            if node_1.type in FUNC_NODE_TYPES:
                func_nodes.append(node_1)
            for node_2 in node_1.children:
                if node_2.type in FUNC_NODE_TYPES:
                    func_nodes.append(node_2)
                for node_3 in node_2.children:
                    if node_3.type in FUNC_NODE_TYPES:
                        func_nodes.append(node_3)
                    for node_4 in node_3.children:
                        if node_4.type in FUNC_NODE_TYPES:
                            func_nodes.append(node_4)
                        for node_5 in node_4.children:
                            if node_5.type in FUNC_NODE_TYPES:
                                func_nodes.append(node_5)
                            for node_6 in node_5.children:
                                if node_6.type in FUNC_NODE_TYPES:
                                    func_nodes.append(node_6)
                                for node_7 in node_6.children:
                                    if node_7.type in FUNC_NODE_TYPES:
                                        func_nodes.append(node_7)

    definitions = []
    for node in func_nodes:
        start_line = node.start_point[0]
        end_line = node.end_point[0]
        definitions.append(
            {
                "function": "".join(lines[start_line : end_line + 1]),
                "start_line": start_line,
                "end_line": end_line,
            }
        )

    return definitions
