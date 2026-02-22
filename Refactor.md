# 🗂️ File Backup Utility — Code Refactoring & Software Engineering Standards Guide

**Course:** Advanced Programming Lab  
**Project:** File Backup Utility (C Language + GTK+ 3)  
**Purpose:** Improve code maintainability, readability, modularity, and scalability  
**Date:** February 2026

---

## 📑 Table of Contents

1. [Executive Summary](#executive-summary)
2. [Naming Conventions](#naming-conventions)
3. [Coding Style Guidelines](#coding-style-guidelines)
4. [Folder Structure](#folder-structure)
5. [Modular Design Principles](#modular-design-principles)
6. [Design Patterns for File Backup Utility](#design-patterns-for-file-backup-utility)
7. [Error Handling & Memory Management](#error-handling--memory-management)
8. [Testing Strategy](#testing-strategy)
9. [Refactoring Roadmap](#refactoring-roadmap)
10. [Future Improvements](#future-improvements)

---

## Executive Summary

### Current Project Overview

The File Backup Utility is a GTK+ 3 desktop application featuring:

**Strengths:**
- Functional file and folder backup system
- Configurable auto-backup with timer scheduling
- Persistent settings via configuration file
- Progress tracking with GTK progress bar
- Backup history log viewer

**Areas for Improvement:**
- Inconsistent naming conventions (no module prefixes)
- Excessive use of global GTK widget pointers
- Tight coupling between UI callbacks and file I/O logic
- Limited modular separation (entire app in one `.c` file)
- Difficult feature extensibility (adding new backup modes requires modifying core functions)

### Refactoring Philosophy

> "Refactor incrementally without breaking backup functionality."

**Goals:**
- Cleaner modular code structure
- Easier debugging and maintenance
- Better scalability for new backup features
- Improved readability for collaborators
- Professional software engineering standards

---

## Naming Conventions

### General Principles

- Use descriptive names with module prefixes
- Avoid cryptic abbreviations
- Maintain consistent casing throughout
- Prefer domain-specific terminology

### Variable Naming Refactoring

#### Before Refactoring
```c
char backup_destination[512];
int auto_backup;
int max_copies;
struct tm *tm;
struct stat st;
```

**Issues:**
- No module ownership visible in name
- Abbreviations like `tm`, `st` reduce clarity
- Hard to understand intent at a glance
- Inconsistent naming style

#### After Refactoring
```c
char backup_destination[MAX_PATH_LENGTH];
int  auto_backup_enabled;
int  max_backup_copies;
struct tm  *time_now;
struct stat file_stat;
```

**Benefits:**
- Self-documenting variables
- Easier debugging
- Consistent `snake_case` style throughout

### Function Naming Refactoring

#### Before
```c
void load_settings();
void save_settings();
void perform_backup();
void add_file_to_list();
void update_status();
void show_notification_msg();
```

**Issues:**
- No module prefix — unclear which module owns the function
- `perform_backup` mixes UI and logic
- `show_notification_msg` is redundant (`msg` suffix unnecessary)

#### After
```c
void settings_manager_load();
void settings_manager_save();
BackupResult backup_engine_run();
void file_utils_add_file_to_list();
void main_window_update_status();
void main_window_show_notification();
```

**Why This Matters:**
- Module prefix (`settings_manager_`, `backup_engine_`, `file_utils_`) shows ownership
- Verb-noun structure clarifies purpose
- Supports modular development and prevents name collisions

### Constants Naming Refactoring

#### Before
```c
#define MAX_PATH 512
#define MAX_ITEMS 1000
#define CONFIG_FILE "backup_config.txt"
#define LOG_FILE "backup_log.txt"
```

#### After
```c
#define MAX_PATH_LENGTH      512
#define MAX_BACKUP_ITEMS     1000
#define CONFIG_FILE_PATH     "backup_config.txt"
#define DEFAULT_BACKUP_DEST  "C:\\Backups"
#define DEFAULT_MAX_COPIES   10
```

**Improvement:**
- Eliminates ambiguity (`MAX_PATH` conflicts with Windows SDK)
- Makes configuration intent explicit
- Groups related constants by domain

### Structure Naming Refactoring

#### Before
```c
typedef struct {
    char backup_destination[MAX_PATH];
    int auto_backup;
    int backup_interval;
    int max_copies;
} BackupSettings;
```

#### After
```c
typedef struct {
    char backup_destination[MAX_PATH_LENGTH]; /**< Output folder for backups       */
    int  auto_backup_enabled;                 /**< 1 = schedule enabled, 0 = off   */
    int  backup_interval_seconds;             /**< Interval between auto-backups   */
    int  max_backup_copies;                   /**< Max versioned copies to keep    */
    int  include_subfolders;                  /**< 1 = recurse into subdirectories */
    int  include_hidden_files;                /**< 1 = include dot/hidden files    */
    int  show_notifications;                  /**< 1 = show popup on completion    */
} BackupSettings;

typedef struct {
    int  files_total;               /**< Total files attempted          */
    int  files_success;             /**< Files copied without error     */
    int  files_failed;              /**< Files that could not be copied */
    char output_directory[MAX_PATH_LENGTH]; /**< Timestamped output folder  */
} BackupResult;

typedef struct {
    GtkWidget    *window;           /**< Top-level application window     */
    GtkWidget    *progress_bar;     /**< Backup progress indicator        */
    GtkWidget    *status_label;     /**< Status message below progress bar*/
    GtkListStore *items_list;       /**< Data model for the file list     */
    GtkWidget    *treeview;         /**< View widget bound to items_list  */
    gboolean      backup_running;   /**< Guard flag: prevents double-start*/
} AppState;
```

**Advantages:**
- `BackupResult` separates output from configuration
- `AppState` groups all GTK widget references — eliminates 9 global variables
- Doxygen field comments make each field's purpose immediately clear

---

## Coding Style Guidelines

### Indentation

- **4 spaces** preferred
- Avoid mixing tabs and spaces
- Align struct fields and assignment operators for readability

**Example:**
```c
BackupSettings settings = {
    .backup_destination      = "C:\\Backups",
    .auto_backup_enabled     = 1,
    .backup_interval_seconds = 300,
    .max_backup_copies       = 10,
};
```

### Line Length

- Recommended maximum ≈ **100 characters**
- Break long function signatures across multiple lines, aligning parameters

```c
/* Good — parameters aligned */
BackupResult backup_engine_run(GtkListStore          *items_list,
                                BackupProgressCallback on_progress,
                                gpointer               user_data);
```

### Section Dividers

Use consistent section dividers inside `.c` files to separate logical blocks:

```c
/* ─── Public API Implementation ──────────────────────────────── */

/* ─── Internal Helpers ───────────────────────────────────────── */

/* ─── Module-Private State ───────────────────────────────────── */
```

### Comment Quality Improvement

#### Before
```c
FILE *src = fopen(source_path, "rb"); // open source file
```

#### After
```c
/*
 * Open source in binary mode to preserve all byte values exactly.
 * Text mode on Windows would corrupt non-text files via CR/LF translation.
 */
FILE *source_file = fopen(source_path, "rb");
```

**Principle:**  
Comments should explain **why**, not just **what**.

### File Headers

Every source file must begin with a Doxygen header:

```c
/**
 * @file    backup_engine.c
 * @brief   Core backup execution — Facade implementation
 *
 * @details Hides all complexity of iterating files, copying them,
 *          managing versioned output directories, and logging results.
 *          The UI layer only needs to call backup_engine_run().
 *
 * @version 2.0.0
 * @date    2026-02-22
 */
```

---

## Folder Structure

### Before Refactoring
```
File-Backup-Utility/
└── backup_utility.c        ← Everything in one file (~450 lines)
```

**Problems:**
- Flat organization — impossible to navigate
- UI, logic, and utilities all entangled
- Adding features means modifying one giant file
- No separation of concerns

### Recommended Structure (After Refactoring)
```
File-Backup-Utility/
├── ver1/
│   └── backup_utility.c            ← Original code preserved
├── ver2/
│   ├── main.c                      ← Entry point only
│   ├── Makefile
│   ├── src/
│   │   ├── core/
│   │   │   ├── backup_engine.c     ← Facade: runs the backup
│   │   │   ├── backup_scheduler.c  ← Auto-backup timer
│   │   │   └── settings_manager.c  ← Singleton: config
│   │   ├── ui/
│   │   │   ├── main_window.c       ← Main GTK window
│   │   │   ├── settings_dialog.c   ← Settings popup
│   │   │   └── log_viewer_dialog.c ← Log history viewer
│   │   └── utils/
│   │       ├── file_utils.c        ← File copy + traversal
│   │       └── logger.c            ← Session log writer
│   └── include/
│       ├── core/
│       ├── ui/
│       └── utils/
├── docs/
│   ├── README.md
│   ├── Implementation.md
│   └── ARCHITECTURE.md
├── LICENSE
└── .gitignore
```

**Benefits:**
- `core/` holds business logic with zero GTK dependency
- `ui/` holds all presentation code
- `utils/` holds reusable helpers
- New backup modes can be added under `core/` without touching `ui/`
- Professional, navigable project layout

---

## Modular Design Principles

### Before Modularization
```c
gboolean perform_backup(gpointer data) {
    backup_running = TRUE;

    /* Count items */
    int total = 0;
    GtkTreeIter count_iter = iter;
    do { total++; } while (gtk_tree_model_iter_next(...));

    /* Create output directory */
    sprintf(backup_dir, "%s\\Backup_%04d...", settings.backup_destination, ...);
    mkdir(backup_dir);

    /* Open log */
    FILE *log = fopen(log_file, "w");

    /* Copy files */
    do {
        FILE *src = fopen(source_path, "rb");
        FILE *dst = fopen(dest_path, "wb");
        /* fread/fwrite loop */

    } while (gtk_tree_model_iter_next(...));

    /* Update GTK progress bar */
    gtk_label_set_text(GTK_LABEL(status_label), status);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), fraction);

    backup_running = FALSE;
}
```

**Problems:**
- Mixed responsibilities: directory creation + file copy + UI update + logging all in one function
- GTK widget calls inside business logic
- Impossible to test file copying without a running GTK app
- Cannot reuse backup logic in a command-line version

### After Modularization
```c
/* backup_engine.c — no GTK widget calls */
BackupResult backup_engine_run(GtkListStore          *items_list,
                                BackupProgressCallback on_progress,
                                gpointer               user_data);

/* file_utils.c — pure file operations */
int  file_utils_copy_file(const char *source, const char *dest);
void file_utils_add_file_to_list(const char *path, GtkListStore *store,
                                  FileProcessorConfig *config);

/* logger.c — pure logging */
int  logger_open(const char *log_path);
void logger_write_file_result(const char *src, const char *dst, int success);
void logger_close(int success, int total);

/* main_window.c — GTK UI only */
void main_window_update_status(AppState *state, const char *msg, double progress);
void main_window_show_notification(GtkWidget *parent, const char *title, const char *msg);
```

### Standard Application Flow
```c
/* main.c */
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    settings_manager_load();
    main_window_create(&g_app_state);

    if (settings_manager_get()->auto_backup_enabled)
        scheduler_start(on_scheduler_trigger, &g_app_state);

    gtk_main();
    scheduler_stop();
    return 0;
}
```

**Advantages:**
- Each module has one clear responsibility
- `backup_engine.c` compiles without GTK — testable in isolation
- New UI frameworks (console, web) can reuse `core/` unchanged
- Easier parallel development

---

## Design Patterns for File Backup Utility

### Singleton Pattern — Settings Management

**Problem:** Global `BackupSettings` accessible and modifiable from anywhere.

**Solution:**
```c
/* settings_manager.h */
BackupSettings *settings_manager_get(void);  /* Only access point */

/* settings_manager.c */
static BackupSettings g_settings = {         /* Hidden from all other modules */
    .backup_destination      = "C:\\Backups",
    .auto_backup_enabled     = 1,
    .backup_interval_seconds = 300,
};
```

**Benefit:** One controlled entry point for all settings reads and writes.

---

### Facade Pattern — Backup Engine

**Problem:** UI had to manage directory creation, file iteration, copying, and logging directly.

**Solution:**
```c
/* One call hides all complexity */
BackupResult result = backup_engine_run(state->items_list,
                                         on_backup_progress,
                                         state);
if (result.files_success == result.files_total)
    main_window_show_notification(state->window, "Done", "Backup complete!");
```

**Benefit:** UI layer is simple and clean; all file system complexity is behind the facade.

---

### Strategy Pattern — File Traversal

**Problem:** Traversal behavior (recurse, include hidden) was hardcoded `if` checks reading global state.

**Solution:**
```c
/* Caller configures behavior — algorithm stays the same */
FileProcessorConfig config = {
    .recurse_subfolders = TRUE,
    .include_hidden     = FALSE
};
file_utils_add_folder_to_list(folder_path, list_store, &config);
```

**Benefit:** Adding new traversal behaviors (e.g. filter by extension) only requires adding a field to `FileProcessorConfig`.

---

### Observer Pattern — Progress Reporting

**Problem:** `perform_backup()` called `gtk_label_set_text()` directly — business logic knew about GTK widgets.

**Solution:**
```c
/* Define the observer interface */
typedef void (*BackupProgressCallback)(const char *filename,
                                        int         current,
                                        int         total,
                                        gpointer    user_data);

/* Engine fires the event — no GTK knowledge */
if (on_progress)
    on_progress(filename, current_index, total, user_data);

/* UI implements the observer */
static void on_backup_progress(const char *filename, int current,
                                 int total, gpointer user_data) {
    AppState *state = (AppState *)user_data;
    char msg[256];
    snprintf(msg, sizeof(msg), "Backing up (%d/%d): %s", current, total, filename);
    main_window_update_status(state, msg, (double)current / total);
}
```

**Benefit:** Backup engine has zero GTK dependency — it can run in any context.

---

## Error Handling & Memory Management

### Safe File Operations
```c
FILE *source_file = fopen(source_path, "rb");
if (!source_file) {
    logger_write(LOG_LEVEL_ERROR, "Failed to open source file");
    return 0;  /* Caller checks return value */
}
```

### GTK Memory Management
```c
/* Always free GTK-allocated strings */
char *path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
if (path) {
    file_utils_add_file_to_list(path, list_store, &config);
    g_free(path);   /* Must use g_free, not free() */
}

/* Always free GSList after use */
GSList *files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
g_slist_free_full(files, g_free);
```

### Ownership Documentation
```c
/**
 * @brief  Returns the singleton BackupSettings instance.
 * @return Pointer to global settings (never NULL, do NOT free).
 */
BackupSettings *settings_manager_get(void);

/**
 * @brief  Copies a file from source to destination.
 * @return 1 on success, 0 on failure. Caller checks return value.
 */
int file_utils_copy_file(const char *source_path, const char *dest_path);
```

### Assertions for Development
```c
#include <assert.h>

assert(items_list != NULL);   /* Catch NULL list at debug time */
assert(strlen(settings_manager_get()->backup_destination) > 0);
```

---

## Testing Strategy

### Functional Tests
- Single file backup copies correctly to destination folder
- Folder backup with recursion includes all nested files
- Auto-backup timer fires at the configured interval
- Settings persist correctly across application restarts

### Boundary Tests
- Backup with empty file list shows appropriate status message
- Very large files (>2GB) copy without truncation
- Destination folder path with spaces handled correctly
- Backup when destination drive is full fails gracefully

### Regression Testing
Ensure refactoring does not break:
- File copy integrity (source and destination byte-identical)
- Settings load/save round-trip (save then reload produces same values)
- Progress bar reaches 1.0 after successful backup completion

### Unit Test Candidates
`file_utils.c` and `logger.c` have zero GTK dependency and can be tested with plain C:
```c
/* Example unit test for file_utils_format_size */
assert(strcmp(format_size_result(512),        "512 B")   == 0);
assert(strcmp(format_size_result(2048),       "2.0 KB")  == 0);
assert(strcmp(format_size_result(1572864),    "1.5 MB")  == 0);
```

---

## Refactoring Roadmap

### Phase 1 — Cleanup
- Fix naming conventions (add module prefixes to all functions)
- Replace bare global variables with `AppState` struct
- Add Doxygen file headers and function documentation
- Replace magic numbers with named constants

### Phase 2 — Modularization
- Extract `backup_engine.c` from `perform_backup()`
- Extract `settings_manager.c` with Singleton accessor
- Extract `file_utils.c` with `FileProcessorConfig` strategy
- Extract `logger.c` with `LogLevel` enum
- Create matching header files for each module

### Phase 3 — UI Separation
- Extract `main_window.c` — remove all global widget pointers
- Extract `settings_dialog.c` — dialog logic separated from settings writes
- Extract `log_viewer_dialog.c` — log search logic separated
- Implement `BackupProgressCallback` Observer interface

### Phase 4 — Feature Expansion
- Implement `max_backup_copies` rotation (delete oldest when limit exceeded)
- Add incremental backup (skip files where `st_mtime` unchanged)
- Add backup verification (compare source and destination checksums)
- Add cross-platform path handling (`G_DIR_SEPARATOR_S`)

---

## Future Improvements

### Backup Features
- Incremental backup — only copy files changed since last backup
- Differential backup — only copy files changed since last full backup
- Backup encryption — password-protect sensitive backup archives
- Remote backup — SFTP/cloud destination support

### Technical Enhancements
- Compression — ZIP backup archives using zlib
- Checksum verification — MD5/SHA256 integrity check after copy
- Background backup thread — non-blocking backup using GLib threads
- Cross-platform support — Linux/macOS path handling

### Software Engineering Improvements
- Unit testing framework — test `file_utils.c` and `logger.c` without GTK
- Continuous integration — GitHub Actions build on every push
- Automatic code formatting — `clang-format` with project style config
- Static analysis — `cppcheck` integration in Makefile

---

## Final Note

This refactoring guide aims to:

✅ Improve code quality through consistent naming and modular structure  
✅ Enhance maintainability by separating UI, core logic, and utilities  
✅ Support future expansion with clean extension points  
✅ Promote professional software engineering practices  
✅ Demonstrate SOLID principles and design patterns in a real C application  

A well-structured File Backup Utility demonstrates not only functional backup capability but also strong software engineering discipline, maintainable layered architecture, and scalability for future enhancements.
