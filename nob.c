#include <string.h>
#define NOB_IMPLEMENTATION
#include "nob.h"

void add_dir_recursively(Nob_Cmd *cmd, const char *dir_path) {
  Nob_File_Paths files = {0};
  nob_read_entire_dir(dir_path, &files);

  for (size_t i = 0; i < files.count; i++) {

    Nob_String_Builder path = {0};
    nob_sb_append_cstr(&path, dir_path);
    nob_sb_append_cstr(&path, "/");
    nob_sb_append_cstr(&path, files.items[i]);
    nob_sb_append_null(&path);

    switch (nob_get_file_type(path.items)) {
    case NOB_FILE_REGULAR: {
      size_t length = strlen(files.items[i]);
      if (strncmp(files.items[i] + (length - 2), ".c", 2) == 0) {
        nob_log(NOB_INFO, "Adding file %s to sources.", path.items);
        nob_cmd_append(cmd, path.items);
      }
      break;
    }

    case NOB_FILE_DIRECTORY:
      if (files.items[i][0] != '.')
        add_dir_recursively(cmd, path.items);
      break;

    case NOB_FILE_SYMLINK:
    case NOB_FILE_OTHER:
      nob_log(NOB_INFO, "Symlink or Unsupported file: %s\n", path.items);
      break;
    }
  }
}

void cc(Nob_Cmd *cmd) {
  nob_cmd_append(cmd, "cc");
  nob_cmd_append(cmd, "-Wall", "-Wextra", "-ggdb");
  nob_cmd_append(cmd, "-O3");
}

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  const char *program = nob_shift_args(&argc, &argv);
  (void)program;

  Nob_Cmd cmd = {0};

  if (!nob_mkdir_if_not_exists("./build/"))
    return 1;

  const char *main_output = "./build/clox";
  cmd.count = 0;
  cc(&cmd);
  nob_cmd_append(&cmd, "-o", main_output);
  add_dir_recursively(&cmd, "./src");
  if (!nob_cmd_run_sync(cmd))
    return 1;

  // cmd.count = 0;
  // nob_cmd_append(&cmd, main_output);
  // nob_da_append_many(&cmd, argv, argc);
  // if (!nob_cmd_run_sync(cmd))
  //   return 1;

  return 0;
}
