#include <iostream>
#include <queue>
#include <tuple>
#include <set>
#include <vector>
#include <string>

inline void move_one(unsigned int& from, unsigned int& to) {
    if (from >= 1) {
        from--;
        to++;
    }
}

inline void move_half(unsigned int& from, unsigned int& to) {
    if (from >= 2) {
        int half = (from % 2 == 0) ? from / 2 : (from - 1) / 2;
        from -= half;
        to += half;
    }
}

bool is_goal_state(const std::vector<unsigned int>& stacks, unsigned int target) {
    for (int stack : stacks) {
        if (stack != target) return false;
    }
    return true;
}

int min_operations(unsigned int total_number, unsigned int num_stack) {
    using namespace std;

    unsigned int target = total_number / num_stack;
    using State = tuple<vector<unsigned int>, unsigned int, string>; // (stacks, steps, path)
    queue<State> q;
    set<vector<unsigned int>> visited;

    vector<unsigned int> initial_stacks(num_stack, 0);
    initial_stacks[0] = total_number;
    q.push({ initial_stacks, 0, "" });
    visited.insert(initial_stacks);

    while (!q.empty()) {
        // using the 1st element of current level(BFS)
        auto [stacks, steps, path] = q.front();
        q.pop();

        // if it's goal state
        if (is_goal_state(stacks, target)) {
            cout << "Path:\n" << path << endl;
            return steps;
        }

        // Try all possible moves
        for (unsigned int i = 0; i < num_stack; ++i) {
            for (unsigned int j = 0; j < num_stack; ++j) {
                if (i != j) {
                    // Create a copy of the current state to explore a new move
                    vector<unsigned int> new_stacks = stacks;

                    // Move one item
                    move_one(new_stacks[i], new_stacks[j]);
                    if (visited.find(new_stacks) == visited.end()) {
                        q.push({ new_stacks, steps + 1, path + "Move one from stack" + to_string(i + 1) + " to stack" + to_string(j + 1) + "\n" });
                        visited.insert(new_stacks);
                    }

                    // Reset new_stacks to the original state
                    new_stacks = stacks;

                    // Move half the items
                    move_half(new_stacks[i], new_stacks[j]);
                    if (visited.find(new_stacks) == visited.end()) {
                        q.push({ new_stacks, steps + 1, path + "Move half from stack" + to_string(i + 1) + " to stack" + to_string(j + 1) + "\n" });
                        visited.insert(new_stacks);
                    }
                }
            }
        }
    }


    return -1; // No solution found
}

void run_operations() 
{
    using namespace std;

    unsigned int total_number;
    unsigned int num_stack;

    cout << "Enter a positive integer for number of stacks: ";
    cin >> num_stack;

    if (cin.fail() || num_stack <= 1) {
        cerr << "Error: number of stacks must be an unsigned integer larger than 1!\n";
        return;
    }

    cout << "Enter a positive integer for total_number: ";
    cin >> total_number;

    if (cin.fail() || total_number == 0 || total_number % num_stack != 0) {
        cerr << "Error: total_number must be a positive integer divisible by num_stack.\n";
        return;
    }

    int min_ops = min_operations(total_number, num_stack);

    if (min_ops != -1) {
        cout << "Minimum operations to achieve " << num_stack << " stacks of " << total_number / num_stack << ": " << min_ops << endl;
    }
    else {
        cout << "No solution found." << endl;
    }
}