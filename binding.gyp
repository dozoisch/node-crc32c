{
    "targets": [
        {
            "target_name": "crc32c",
            "sources": [ "src/crc32c.cpp", "src/impl.c" ]
        },
        {
            "target_name": "after_build",
            "type": "none",
            "dependencies": [ "crc32c" ],
            "actions" : [
                {
                    "action_name": "symlink",
                    "inputs": [ "<@(PRODUCT_DIR)/crc32c.node" ],
                    "outputs": [ "<(module_root_dir)/bin/crc32c.node" ],
                    "action": [
                        "ln", "-fs",
                        "<@(PRODUCT_DIR)/crc32c.node",
                        "<(module_root_dir)/bin/crc32c.node"
                    ]
                }
            ]
        }
    ]
}
