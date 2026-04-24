#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#define MAX_ROWS 999
#define MAX_COLS 18278  // ZZZ = 26^3 + 26^2 + 26
#define MAX_FORMULA_LEN 100
#define DISPLAY_SIZE 10
#define MAX_DEPENDENTS 100
#define COMMAND_SIZE 200
#define MAX_CELL_REF_LEN 10  // e.g., "A1" has 2 characters, adjust as needed


typedef struct {
    int value;
    char *formula;
    int is_formula;
    char **dependents;  // Cells that depend on this cell
    int dependent_count;
    int max_dependents;
} Cell;

typedef struct {
    Cell **cells;
    int rows;
    int cols;
    int view_row;
    int view_col;
    int output_enabled;
} Sheet;

// Global sheet instance
Sheet *sheet = NULL;

// Function declarations
Sheet* create_sheet(int rows, int cols);
void free_sheet(Sheet *sheet);
int decode_column(const char *col_str);
void encode_column(int col, char *col_str);
int parse_cell_reference(const char *ref, int *row, int *col);
void display_sheet(Sheet *sheet);
int evaluate_expression(const char *expr, const char *current_cell);
void update_cell(const char *cell_ref, const char *formula);
void recalculate_dependents(const char *cell_ref);
int has_circular_dependency(const char *start_cell, const char *formula);
double calculate_range_function(const char *function, const char *range);
void* sleep_thread(void *duration);
void scroll_sheet(Sheet *sheet, char direction);
void scroll_to_cell(Sheet *sheet, const char *cell_ref);
void process_command(Sheet *sheet, const char *command);
int evaluate_arithmetic(const char *expr);
void update_dependents(const char *cell_ref, const char *formula);
int evaluate_range_function(const char *range);

// Main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <rows> <columns>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    if (rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS) {
        printf("Invalid dimensions. Rows: 1-%d, Columns: 1-%d\n", MAX_ROWS, MAX_COLS);
        return 1;
    }

    sheet = create_sheet(rows, cols);
    if (!sheet) {
        printf("Failed to create sheet\n");
        return 1;
    }

    char command[COMMAND_SIZE];
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        if (sheet->output_enabled) {
            display_sheet(sheet);
        }
        printf("[0.0] (ok) > ");
        
        if (!fgets(command, COMMAND_SIZE, stdin)) {
            break;
        }
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "q") == 0) {
            break;
        }

        start = clock();
        process_command(sheet, command);
        end = clock();
        
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("[%.1f] (ok)\n", cpu_time_used);
    }

    free_sheet(sheet);
    return 0;
}

// Create a new sheet
Sheet* create_sheet(int rows, int cols) {
    Sheet *s = malloc(sizeof(Sheet));
    if (!s) return NULL;

    s->rows = rows;
    s->cols = cols;
    s->view_row = 0;
    s->view_col = 0;
    s->output_enabled = 1;

    s->cells = malloc(rows * sizeof(Cell*));
    if (!s->cells) {
        free(s);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        s->cells[i] = malloc(cols * sizeof(Cell));
        if (!s->cells[i]) {
            for (int j = 0; j < i; j++) {
                free(s->cells[j]);
            }
            free(s->cells);
            free(s);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            s->cells[i][j].value = 0;
            s->cells[i][j].formula = NULL;
            s->cells[i][j].is_formula = 0;
            s->cells[i][j].dependents = NULL;
            s->cells[i][j].dependent_count = 0;
            s->cells[i][j].max_dependents = 0;
        }
    }

    return s;
}

// Process user commands
void process_command(Sheet *sheet, const char *command) {
    if (!command || !*command) return;

    // Handle navigation commands
    if (strlen(command) == 1) {
        switch (command[0]) {
            case 'w': scroll_sheet(sheet, 'w'); return;
            case 'a': scroll_sheet(sheet, 'a'); return;
            case 's': scroll_sheet(sheet, 's'); return;
            case 'd': scroll_sheet(sheet, 'd'); return;
        }
    }

    // Handle output control commands
    if (strcmp(command, "disable_output") == 0) {
        sheet->output_enabled = 0;
        return;
    }
    if (strcmp(command, "enable_output") == 0) {
        sheet->output_enabled = 1;
        return;
    }

    // Handle scroll_to command
    if (strncmp(command, "scroll_to ", 9) == 0) {
        scroll_to_cell(sheet, command + 9);
        return;
    }

    // Handle cell assignments
    char *equals = strchr(command, '=');
    if (!equals) {
        printf("Invalid command format\n");
        return;
    }

    char cell_ref[10] = {0};
    strncpy(cell_ref, command, equals - command);
    update_cell(cell_ref, equals + 1);
}

// Update cell value and formula
void update_cell(const char *cell_ref, const char *formula) {
    int row, col;
    if (!parse_cell_reference(cell_ref, &row, &col)) {
        printf("Invalid cell reference\n");
        return;
    }

    // Check for circular dependency
    if (has_circular_dependency(cell_ref, formula)) {
        printf("Circular dependency detected\n");
        return;
    }

    // Free old formula if it exists
    if (sheet->cells[row][col].formula) {
        free(sheet->cells[row][col].formula);
    }

    // Update formula
    sheet->cells[row][col].formula = strdup(formula);
    sheet->cells[row][col].is_formula = 1;

    // Evaluate new value
    int new_value = evaluate_expression(formula, cell_ref);
    sheet->cells[row][col].value = new_value;

    // Update the dependents of this cell
    // For each cell that depends on this one, recalculate it
    recalculate_dependents(cell_ref);

    // Add this cell as a dependent for other cells
    // You need to parse the formula and update the dependents list accordingly
    // (you need to find all cells referenced in the formula and mark them as dependents)
    update_dependents(cell_ref, formula);
}

// Update the dependent list of other cells based on the formula
// Update the dependent list of other cells based on the formula
void update_dependents(const char *cell_ref, const char *formula) {
    char *formula_copy = strdup(formula);
    char token = strtok(formula_copy, "+-/() ");
    while (token) {
        if (isalpha(token[0])) {  // Possible cell reference
            int dep_row, dep_col;
            if (parse_cell_reference(token, &dep_row, &dep_col)) {
                // Add this cell to the dependent's dependents list
                if (sheet->cells[dep_row][dep_col].dependent_count >= 
                    sheet->cells[dep_row][dep_col].max_dependents) {
                    // Increase max_dependents if necessary
                    sheet->cells[dep_row][dep_col].max_dependents *= 2;
                    sheet->cells[dep_row][dep_col].dependents = realloc(
                        sheet->cells[dep_row][dep_col].dependents,
                        sheet->cells[dep_row][dep_col].max_dependents * sizeof(char*)
                    );
                }
                sheet->cells[dep_row][dep_col].dependents[sheet->cells[dep_row][dep_col].dependent_count] = strdup(cell_ref);
                sheet->cells[dep_row][dep_col].dependent_count++;
            }
        }
        // Handle range-based formulas like SUM(A1:B5)
        else if (strchr(token, ':')) {  // It's a range
            char *start_cell = strtok(token, ":");
            char *end_cell = strtok(NULL, ":");

            int start_row, start_col, end_row, end_col;
            if (parse_cell_reference(start_cell, &start_row, &start_col) &&
                parse_cell_reference(end_cell, &end_row, &end_col)) {
                // Iterate over the range and track each cell as a dependent
                for (int row = start_row; row <= end_row; row++) {
                    for (int col = start_col; col <= end_col; col++) {
                        char dependent_cell[MAX_CELL_REF_LEN];
                        snprintf(dependent_cell, MAX_CELL_REF_LEN, "%c%d", col + 'A', row + 1);
                        if (sheet->cells[row][col].dependent_count >= 
                            sheet->cells[row][col].max_dependents) {
                            sheet->cells[row][col].max_dependents *= 2;
                            sheet->cells[row][col].dependents = realloc(
                                sheet->cells[row][col].dependents,
                                sheet->cells[row][col].max_dependents * sizeof(char*)
                            );
                        }
                        sheet->cells[row][col].dependents[sheet->cells[row][col].dependent_count] = strdup(cell_ref);
                        sheet->cells[row][col].dependent_count++;
                    }
                }
            }
        }

        token = strtok(NULL, "+-*/() ");
    }
    free(formula_copy);
}



// Convert column reference (e.g., "A", "BC") to number (0-based)
int decode_column(const char *col_str) {
    int col = 0;
    for (int i = 0; col_str[i] && isalpha(col_str[i]); i++) {
        col = col * 26 + (toupper(col_str[i]) - 'A' + 1);
    }
    return col - 1;  // Convert to 0-based index
}

// Convert column number to letter reference (e.g., 0 -> "A", 27 -> "AB")
void encode_column(int col, char *col_str) {
    int idx = 0;
    col++; // Convert to 1-based for calculation

    while (col > 0) {
        col--;
        col_str[idx++] = 'A' + (col % 26);
        col /= 26;
    }
    col_str[idx] = '\0';
    
    // Reverse the string
    for (int i = 0; i < idx/2; i++) {
        char temp = col_str[i];
        col_str[i] = col_str[idx-1-i];
        col_str[idx-1-i] = temp;
    }
}

// Parse cell reference (e.g., "A1", "BC23") into row and column numbers
int parse_cell_reference(const char *ref, int *row, int *col) {
    if (!ref || !*ref) return 0;

    // Find where numbers start
    const char *num_start = ref;
    while (*num_start && isalpha(*num_start)) num_start++;
    if (!*num_start) return 0;

    // Extract column letters
    char col_str[10] = {0};
    strncpy(col_str, ref, num_start - ref);
    *col = decode_column(col_str);

    // Extract row number
    *row = atoi(num_start) - 1;  // Convert to 0-based index

    return (*row >= 0 && *row < sheet->rows && *col >= 0 && *col < sheet->cols);
}

// Parse a range (e.g., "A1:B2") into start and end positions
int parse_range(const char *range, int *start_row, int *start_col, int *end_row, int *end_col) {
    char range_copy[MAX_FORMULA_LEN];
    strncpy(range_copy, range, MAX_FORMULA_LEN-1);
    range_copy[MAX_FORMULA_LEN-1] = '\0';

    char *colon = strchr(range_copy, ':');
    if (!colon) return 0;
    *colon = '\0';

    char *start = range_copy;
    char *end = colon + 1;

    if (!parse_cell_reference(start, start_row, start_col) ||
        !parse_cell_reference(end, end_row, end_col)) {
        return 0;
    }

    return (*start_row <= *end_row && *start_col <= *end_col);
}

// Calculate statistical functions over a range
double calculate_range_function(const char *function, const char *range) {
    int start_row, start_col, end_row, end_col;
    if (!parse_range(range, &start_row, &start_col, &end_row, &end_col)) {
        return 0;
    }

    int count = 0;
    double sum = 0;
    int min = INT_MAX;
    int max = INT_MIN;
    double mean = 0;
    double variance = 0;

    // First pass: calculate sum, min, max, and count
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_col; j <= end_col; j++) {
            int value = sheet->cells[i][j].value;
            sum += value;
            if (value < min) min = value;
            if (value > max) max = value;
            count++;
        }
    }

    if (count == 0) return 0;
    mean = sum / count;

    // Calculate standard deviation if needed
    if (strcmp(function, "STDEV") == 0) {
        for (int i = start_row; i <= end_row; i++) {
            for (int j = start_col; j <= end_col; j++) {
                double diff = sheet->cells[i][j].value - mean;
                variance += diff * diff;
            }
        }
        return sqrt(variance / count);
    }

    if (strcmp(function, "MIN") == 0) return min;
    if (strcmp(function, "MAX") == 0) return max;
    if (strcmp(function, "SUM") == 0) return sum;
    if (strcmp(function, "AVG") == 0) return mean;

    return 0;
}

// Thread function for SLEEP
void* sleep_thread(void *arg) {
    int duration = (int)arg;
    sleep(duration);
    free(arg);
    return NULL;
}

// Evaluate a formula
// Evaluate a formula
// Evaluate a formula
int evaluate_expression(const char *expr, const char *current_cell) {
    char expr_copy[MAX_FORMULA_LEN];
    strncpy(expr_copy, expr, MAX_FORMULA_LEN-1);
    expr_copy[MAX_FORMULA_LEN-1] = '\0';

    // Handle direct number
    char *endptr;
    long value = strtol(expr_copy, &endptr, 10);
    if (*expr_copy && !*endptr) return (int)value;

    // Handle single cell reference
    if (isalpha(expr_copy[0]) && !strchr(expr_copy, '+') && 
        !strchr(expr_copy, '-') && !strchr(expr_copy, '*') && 
        !strchr(expr_copy, '/') && !strchr(expr_copy, '(')) {
        int row, col;
        if (parse_cell_reference(expr_copy, &row, &col)) {
            return sheet->cells[row][col].value;
        }
    }

    // Handle functions
    char function[20] = {0};
    char args[MAX_FORMULA_LEN] = {0};
    if (sscanf(expr_copy, "%[A-Z](%[^)])", function, args) == 2) {
        if (strcmp(function, "SLEEP") == 0) {
            int *duration = malloc(sizeof(int));
            *duration = atoi(args);
            pthread_t thread;
            pthread_create(&thread, NULL, sleep_thread, duration);
            pthread_detach(thread);
            return *duration;
        }
        return (int)calculate_range_function(function, args);
    }

    // Handle complex arithmetic expressions or ranges
    char final_expr[MAX_FORMULA_LEN] = "";
    char *pos = expr_copy;
    char token[MAX_FORMULA_LEN];
    int idx = 0;

    // Parse and replace cell references with values
    while (*pos) {
        if (isalpha(*pos)) {  // Cell reference
            int i = 0;
            while (isalnum(*pos)) {
                token[i++] = *pos++;
            }
            token[i] = '\0';
            
            int row, col;
            if (parse_cell_reference(token, &row, &col)) {
                char num_str[20];
                snprintf(num_str, sizeof(num_str), "%d", sheet->cells[row][col].value);
                strcat(final_expr, num_str);
                idx = strlen(final_expr);
            } else {
                return 0;  // Invalid reference
            }
        } else if (isdigit(*pos)) {  // Number
            while (isdigit(*pos)) {
                final_expr[idx++] = *pos++;
            }
            final_expr[idx] = '\0';
        } else if (pos == '+' || *pos == '-' || *pos == '' || *pos == '/') {
            // Add space before operator
            if (idx > 0 && final_expr[idx-1] != ' ') {
                final_expr[idx++] = ' ';
            }
            final_expr[idx++] = *pos++;
            // Add space after operator
            final_expr[idx++] = ' ';
            final_expr[idx] = '\0';
        } else if (*pos == ':') {
            // Handle range (e.g., A1:B5) by evaluating the range
            char range[MAX_CELL_REF_LEN * 2];  // For example, A1:B5
            int i = 0;
            while (*pos && (*pos == ':' || isalnum(*pos) || *pos == '$')) {
                range[i++] = *pos++;
            }
            range[i] = '\0';

            // Call function to handle the range (e.g., sum, stdev)
            return evaluate_range_function(range);
        } else {
            pos++;  // Skip other characters
        }
    }

    return evaluate_arithmetic(final_expr);
}

// Evaluate range functions like SUM(A1:B5)
int evaluate_range_function(const char *range) {
    char start_cell[MAX_CELL_REF_LEN], end_cell[MAX_CELL_REF_LEN];
    if (sscanf(range, "%[^:]:%s", start_cell, end_cell) != 2) {
        return 0;  // Invalid range
    }

    int start_row, start_col, end_row, end_col;
    if (parse_cell_reference(start_cell, &start_row, &start_col) &&
        parse_cell_reference(end_cell, &end_row, &end_col)) {
        int sum = 0;
        int count = 0;

        for (int row = start_row; row <= end_row; row++) {
            for (int col = start_col; col <= end_col; col++) {
                sum += sheet->cells[row][col].value;
                count++;
            }
        }
        return sum;
    }
    return 0;  // Return 0 if the range is invalid
}



int evaluate_arithmetic(const char *expr) {
    // Handle simple arithmetic first
    int a = 0, b = 0;
    char op = 0;
    if (sscanf(expr, "%d%c%d", &a, &op, &b) == 3) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b != 0 ? a / b : 0;
        }
    }

    char expr_copy[MAX_FORMULA_LEN];
    strncpy(expr_copy, expr, MAX_FORMULA_LEN-1);
    expr_copy[MAX_FORMULA_LEN-1] = '\0';

    // Parse complex expressions with operator precedence
    char *tokens[MAX_FORMULA_LEN];
    int token_count = 0;
    
    // Tokenize with space as delimiter
    char *token = strtok(expr_copy, " ");
    while (token && token_count < MAX_FORMULA_LEN) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    if (token_count == 0) return 0;
    if (token_count == 1) return atoi(tokens[0]);

    // First pass: handle multiplication and division
    int i = 1;
    while (i < token_count - 1) {
        if (tokens[i] == '' || *tokens[i] == '/') {
            int a = atoi(tokens[i-1]);
            int b = atoi(tokens[i+1]);
            int result;
            
            if (tokens[i] == '') {
                result = a * b;
            } else {
                if (b == 0) return 0;  // Handle division by zero
                result = a / b;
            }
            
            sprintf(tokens[i-1], "%d", result);
            
            // Shift remaining tokens left
            for (int j = i; j < token_count - 2; j++) {
                tokens[j] = tokens[j+2];
            }
            token_count -= 2;
            continue;
        }
        i++;
    }

    // Second pass: handle addition and subtraction
    int result = atoi(tokens[0]);
    for (i = 1; i < token_count - 1; i += 2) {
        int next_num = atoi(tokens[i+1]);
        if (*tokens[i] == '+') {
            result += next_num;
        } else if (*tokens[i] == '-') {
            result -= next_num;
        }
    }

    return result;
}

// Display the current view of the sheet
void display_sheet(Sheet *sheet) {
    if (!sheet->output_enabled) return;

    // Calculate max width for each column
    int max_widths[DISPLAY_SIZE] = {0};
    for (int j = sheet->view_col; j < sheet->view_col + DISPLAY_SIZE && j < sheet->cols; j++) {
        char col_header[10];
        encode_column(j, col_header);
        max_widths[j - sheet->view_col] = strlen(col_header);
    }

    // Find max cell width for each column
    for (int i = sheet->view_row; i < sheet->view_row + DISPLAY_SIZE && i < sheet->rows; i++) {
        for (int j = sheet->view_col; j < sheet->view_col + DISPLAY_SIZE && j < sheet->cols; j++) {
            int val = sheet->cells[i][j].value;
            int width = (val == 0) ? 1 : snprintf(NULL, 0, "%d", val);
            if (width > max_widths[j - sheet->view_col]) {
                max_widths[j - sheet->view_col] = width;
            }
        }
    }

    // Print column headers with dynamic width
    printf("    ");  // Space for row numbers
    for (int j = sheet->view_col; j < sheet->view_col + DISPLAY_SIZE && j < sheet->cols; j++) {
        char col_header[10];
        encode_column(j, col_header);
        printf("%-*s ", max_widths[j - sheet->view_col], col_header);
    }
    printf("\n");

    // Print rows with dynamically sized columns
    for (int i = sheet->view_row; i < sheet->view_row + DISPLAY_SIZE && i < sheet->rows; i++) {
        printf("%-4d", i + 1);  // Row number
        for (int j = sheet->view_col; j < sheet->view_col + DISPLAY_SIZE && j < sheet->cols; j++) {
            printf("%-*d ", max_widths[j - sheet->view_col], sheet->cells[i][j].value);
        }
        printf("\n");
    }
}

// Check for circular dependencies
int has_circular_dependency(const char *start_cell, const char *formula) {
    if (!formula || !*formula) return 0;

    int start_row, start_col;
    if (!parse_cell_reference(start_cell, &start_row, &start_col)) return 1;

    // Extract cell references from formula
    char *formula_copy = strdup(formula);
    char token = strtok(formula_copy, "+-/() ");

    while (token) {
        if (isalpha(token[0])) {  // Possible cell reference
            int row, col;
            if (parse_cell_reference(token, &row, &col)) {
                if (row == start_row && col == start_col) {
                    free(formula_copy);
                    return 1;
                }
            }
        }
        token = strtok(NULL, "+-*/() ");
    }

    free(formula_copy);
    return 0;
}

// Scroll the sheet view
void scroll_sheet(Sheet *sheet, char direction) {
    switch (direction) {
        case 'w':  // up
            if (sheet->view_row > 0) sheet->view_row -= DISPLAY_SIZE;
            break;
        case 's':  // down
            if (sheet->view_row + DISPLAY_SIZE < sheet->rows) sheet->view_row += DISPLAY_SIZE;
            break;
        case 'a':  // left
            if (sheet->view_col > 0) sheet->view_col -= DISPLAY_SIZE;
            break;
        case 'd':  // right
            if (sheet->view_col + DISPLAY_SIZE < sheet->cols) sheet->view_col += DISPLAY_SIZE;
            break;
    }
}

// Scroll to specific cell
void scroll_to_cell(Sheet *sheet, const char *cell_ref) {
    int row, col;
    if (!parse_cell_reference(cell_ref, &row, &col)) {
        printf("Invalid cell reference for scroll\n");
        return;
    }

    sheet->view_row = (row / DISPLAY_SIZE) * DISPLAY_SIZE;
    sheet->view_col = (col / DISPLAY_SIZE) * DISPLAY_SIZE;
}

// Recalculate cells that depend on the changed cell
void recalculate_dependents(const char *cell_ref) {
    int row, col;
    if (!parse_cell_reference(cell_ref, &row, &col)) return;

    Cell *cell = &sheet->cells[row][col];
    for (int i = 0; i < cell->dependent_count; i++) {
        const char *dependent = cell->dependents[i];
        int dep_row, dep_col;
        if (parse_cell_reference(dependent, &dep_row, &dep_col)) {
            if (sheet->cells[dep_row][dep_col].is_formula) {
                int new_value = evaluate_expression(sheet->cells[dep_row][dep_col].formula, dependent);
                sheet->cells[dep_row][dep_col].value = new_value;
                recalculate_dependents(dependent);
            }
        }
    }
}

// Free all allocated memory
void free_sheet(Sheet *sheet) {
    if (!sheet) return;

    for (int i = 0; i < sheet->rows; i++) {
        for (int j = 0; j < sheet->cols; j++) {
            Cell *cell = &sheet->cells[i][j];
            if (cell->formula) free(cell->formula);
            if (cell->dependents) {
                for (int k = 0; k < cell->max_dependents; k++) {
                    free(cell->dependents[k]);
                }
                free(cell->dependents);
            }
        }
        free(sheet->cells[i]);
    }
    free(sheet->cells);
    free(sheet);
}