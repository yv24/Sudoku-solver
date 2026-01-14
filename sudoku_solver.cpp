class SudokuSolver {
private:
    int grid[9][9];
    
    // Check if placing num at grid[row][col] is valid
    bool isValid(int row, int col, int num) {
        // Check row
        for (int x = 0; x < 9; x++) {
            if (grid[row][x] == num) return false;
        }
        
        // Check column
        for (int x = 0; x < 9; x++) {
            if (grid[x][col] == num) return false;
        }
        
        // Check 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }
        
        return true;
    }
    
    // Validate initial puzzle for conflicts
    bool validatePuzzle() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] != 0) {
                    int num = grid[row][col];
                    grid[row][col] = 0; // Temporarily remove
                    if (!isValid(row, col, num)) {
                        grid[row][col] = num; // Restore
                        return false;
                    }
                    grid[row][col] = num; // Restore
                }
            }
        }
        return true;
    }
    
    // Count number of solutions
    int countSolutions(int count = 0) {
        if (count > 1) return count; // Stop if multiple solutions found
        
        int row = -1, col = -1;
        bool isEmpty = false;
        
        // Find empty cell
        for (int i = 0; i < 9 && !isEmpty; i++) {
            for (int j = 0; j < 9 && !isEmpty; j++) {
                if (grid[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                }
            }
        }
        
        if (!isEmpty) return count + 1; // No empty cell, solution found
        
        // Try digits 1-9
        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                grid[row][col] = num;
                count = countSolutions(count);
                grid[row][col] = 0; // Backtrack
            }
        }
        
        return count;
    }
    
    // Backtracking solver
    bool solveSudoku() {
        int row = -1, col = -1;
        bool isEmpty = false;
        
        // Find empty cell
        for (int i = 0; i < 9 && !isEmpty; i++) {
            for (int j = 0; j < 9 && !isEmpty; j++) {
                if (grid[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                }
            }
        }
        
        if (!isEmpty) return true; // No empty cell, puzzle solved
        
        // Try digits 1-9
        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                grid[row][col] = num;
                if (solveSudoku()) return true;
                grid[row][col] = 0; // Backtrack
            }
        }
        
        return false;
    }

public:
    // Load hardcoded default puzzle
    void loadHardcoded() {
        int puzzle[9][9] = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = puzzle[i][j];
            }
        }
    }
    
    // Load puzzle from file
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file '" << filename << "'" << endl;
            return false;
        }
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!(file >> grid[i][j])) {
                    cout << "Error: Invalid file format" << endl;
                    file.close();
                    return false;
                }
            }
        }
        
        file.close();
        return true;
    }
    
    // Manual input from console
    void loadManual() {
        cout << "Enter the Sudoku puzzle (9x9 grid, use 0 for empty cells):" << endl;
        for (int i = 0; i < 9; i++) {
            cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < 9; j++) {
                cin >> grid[i][j];
            }
        }
    }
    
    // Display puzzle in console
    void display() {
        cout << "\n+-------+-------+-------+" << endl;
        for (int i = 0; i < 9; i++) {
            cout << "| ";
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0) cout << ". ";
                else cout << grid[i][j] << " ";
                
                if ((j + 1) % 3 == 0) cout << "| ";
            }
            cout << endl;
            if ((i + 1) % 3 == 0) cout << "+-------+-------+-------+" << endl;
        }
    }
    
    // Save results to text file
    void saveToTxt(const string& filename, double timeTaken) {
        ofstream file(filename);
        file << "SUDOKU SOLVER - RESULT\n";
        file << "======================\n\n";
        file << "Solved Puzzle:\n\n";
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                file << grid[i][j] << " ";
                if ((j + 1) % 3 == 0) file << "  ";
            }
            file << "\n";
            if ((i + 1) % 3 == 0) file << "\n";
        }
        
        file << "\nExecution Time: " << timeTaken << " ms\n";
        file.close();
        cout << "Results saved to " << filename << endl;
    }
    
    // Save results to HTML file
    void saveToHtml(const string& filename, double timeTaken) {
        ofstream file(filename);
        file << "<!DOCTYPE html>\n<html>\n<head>\n";
        file << "<title>Sudoku Solver Result</title>\n";
        file << "<style>\n";
        file << "body { font-family: Arial, sans-serif; margin: 50px; background: #f0f0f0; }\n";
        file << "h1 { color: #333; }\n";
        file << "table { border-collapse: collapse; margin: 20px auto; background: white; }\n";
        file << "td { width: 40px; height: 40px; text-align: center; font-size: 18px; border: 1px solid #ccc; }\n";
        file << ".thick-border-right { border-right: 3px solid #333; }\n";
        file << ".thick-border-bottom { border-bottom: 3px solid #333; }\n";
        file << ".stats { text-align: center; margin-top: 20px; font-size: 16px; }\n";
        file << "</style>\n</head>\n<body>\n";
        file << "<h1 style='text-align:center;'>Sudoku Solver - Result</h1>\n";
        file << "<table>\n";
        
        for (int i = 0; i < 9; i++) {
            file << "<tr>\n";
            for (int j = 0; j < 9; j++) {
                file << "<td";
                if ((j + 1) % 3 == 0 && j != 8) file << " class='thick-border-right'";
                if ((i + 1) % 3 == 0 && i != 8) file << " class='thick-border-bottom'";
                file << ">" << grid[i][j] << "</td>\n";
            }
            file << "</tr>\n";
        }
        
        file << "</table>\n";
        file << "<div class='stats'><strong>Execution Time:</strong> " << timeTaken << " ms</div>\n";
        file << "</body>\n</html>";
        file.close();
        cout << "HTML results saved to " << filename << endl;
    }
    
    // Main solve function
    void solve() {
        cout << "\n========== SUDOKU SOLVER ==========" << endl;
        cout << "\nOriginal Puzzle:" << endl;
        display();
        
        // Validate puzzle
        if (!validatePuzzle()) {
            cout << "\nError: Invalid puzzle! Contains conflicts." << endl;
            return;
        }
        
        cout << "\nValidation: PASSED ✓" << endl;
        
        // Count solutions
        int originalGrid[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                originalGrid[i][j] = grid[i][j];
            }
        }
        
        int solutionCount = countSolutions(0);
        
        // Restore grid
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = originalGrid[i][j];
            }
        }
        
        if (solutionCount == 0) {
            cout << "Solution Analysis: No solution exists" << endl;
            return;
        } else if (solutionCount == 1) {
            cout << "Solution Analysis: Unique solution ✓" << endl;
        } else {
            cout << "Solution Analysis: Multiple solutions exist" << endl;
        }
        
        // Solve with timing
        cout << "\nSolving..." << endl;
        auto start = high_resolution_clock::now();
        bool solved = solveSudoku();
        auto end = high_resolution_clock::now();
        
        double timeTaken = duration_cast<microseconds>(end - start).count() / 1000.0;
        
        if (solved) {
            cout << "\n✓ PUZZLE SOLVED SUCCESSFULLY!" << endl;
            cout << "\nSolved Puzzle:" << endl;
            display();
            cout << "\nExecution Time: " << timeTaken << " ms" << endl;
            
            // Save results
            saveToTxt("output.txt", timeTaken);
            saveToHtml("output.html", timeTaken);
        } else {
            cout << "\nCould not solve the puzzle." << endl;
        }
    }
};

int main() {
    SudokuSolver solver;
    
    cout << "========== SUDOKU SOLVER ==========" << endl;
    cout << "\nSelect Input Method:" << endl;
    cout << "1. Hardcoded Default Puzzle" << endl;
    cout << "2. Load from File (input1.txt)" << endl;
    cout << "3. Manual Input" << endl;
    cout << "\nEnter your choice (1-3): ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1:
            solver.loadHardcoded();
            cout << "\nLoaded hardcoded puzzle." << endl;
            break;
        case 2:
            if (!solver.loadFromFile("input1.txt")) {
                cout << "Falling back to hardcoded puzzle..." << endl;
                solver.loadHardcoded();
            } else {
                cout << "\nLoaded puzzle from file." << endl;
            }
            break;
        case 3:
            solver.loadManual();
            break;
        default:
            cout << "\nInvalid choice. Using hardcoded puzzle." << endl;
            solver.loadHardcoded();
    }
    
    solver.solve();
    
    return 0;
}