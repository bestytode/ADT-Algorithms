#include <iostream>
#include <queue>
#include <tuple>
#include <set>
#include <vector>
#include <string>

inline void move_one(unsigned int& from, unsigned int& to) noexcept {
    if (from >= 1) {
        from--;
        to++;
    }
}

inline void move_half(unsigned int& from, unsigned int& to) noexcept {
    if (from >= 2) {
        int half = (from % 2 == 0) ? from / 2 : (from - 1) / 2;
        from -= half;
        to += half;
    }
}

bool is_goal_state(const std::vector<unsigned int>& stacks, unsigned int target) noexcept {
	for (unsigned int stack : stacks) {
		if (stack != target)
			return false;
	}
	return true;
}

// return the minimum operation count, return -1 if not found.
int min_operations(unsigned int total_number, unsigned int num_stack, unsigned int target) {
    using namespace std;

    // Define a state as a tuple containing stacks, steps, and path
    using State = tuple<vector<unsigned int>, unsigned int, string>;
    queue<State> q; // Queue for BFS
    set<vector<unsigned int>> visited; // Set to track visited states

    // Initialize the starting state
    vector<unsigned int> initial_stacks(num_stack, 0);
    initial_stacks[0] = total_number;
    q.push({ initial_stacks, 0, "" });
    visited.insert(initial_stacks);

    while (!q.empty()) {
        // Get the current state from the front of the queue
        // Copies the elements to ensure validity after q.pop() is called
        auto [stacks, steps, path] = q.front();
        q.pop();

        // Check if the goal state is reached
        if (is_goal_state(stacks, target)) {
            cout << "Path:\n" << path << endl;
            return steps;
        }

        // Try all possible moves from each stack to every other stack
		for (unsigned int i = 0; i < num_stack; ++i) {
			for (unsigned int j = 0; j < num_stack; ++j) {
				if (i != j) {
					// Create a copy of the current state
					vector<unsigned int> new_stacks = stacks;
					move_one(new_stacks[i], new_stacks[j]);

					// If the new state is not visited, push it to the queue and mark it as visited
					if (visited.find(new_stacks) == visited.end()) {
						q.push({ new_stacks, steps + 1, path + "Move 1 from stack" + to_string(i + 1) + " to stack" + to_string(j + 1) + "\n" });
						visited.insert(new_stacks);
					}

					// Reset new_stacks to the original state
					new_stacks = stacks;

					move_half(new_stacks[i], new_stacks[j]);
					if (visited.find(new_stacks) == visited.end()) {
						q.push({ new_stacks, steps + 1, path + "Move 1/2 from stack" + to_string(i + 1) + " to stack" + to_string(j + 1) + "\n" });
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
    unsigned int total_number;
    unsigned int num_stack;
    unsigned int target;

    std::cout << "Enter a positive integer for number of stacks: ";
    std::cin >> num_stack;

    if (std::cin.fail() || num_stack <= 1) {
        std::cerr << "Error: number of stacks must be an unsigned integer larger than 1!\n";
        return;
    }

    std::cout << "Enter a positive integer for total_number: ";
    std::cin >> total_number;

    if (std::cin.fail() || total_number == 0 || total_number % num_stack != 0) {
        std::cerr << "Error: total_number must be a positive integer divisible by num_stack.\n";
        return;
    }

    target = total_number / num_stack;
    int min_ops = min_operations(total_number, num_stack, target);

    if (min_ops != -1) {
        std::cout << "Minimum operations to achieve " << num_stack << " stacks of same number: " << min_ops << std::endl;
    }
    else {
        std::cout << "No solution found." << std::endl;
    }
}