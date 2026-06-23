/** @DESCRIPTION
 *  We now consider assigning tasks to workers. Each worker must be assigned
 *  exactly two tasks. Each task takes a fixed amount of time. Tasks are
 *  independent, i.e., there are no constraints of the form "Task 4 cannot
 *  start before Task 3 is completed." Any task can be assigned to any worker.
 *
 *  Design an algorithm that takes as input a set of tasks and returns an
 *  optimum assignment.
 *
 *  Hint: What additional task should be assigned to the worker who is assigned
 *        the longest task?
 */

#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
public:
    /** @IDEA
     *  Greedily assign one time-consuming and one not time-consuming task to
     *  a worker. Record the max time cost.
     *
     *  The greedy make sense in a way that,
     *  if we looking at any assignment in which a longest task is not paired
     *  with the shortest task. By swapping the task that the longest task is
     *  currently paired with with the shortest task, we get an assignment
     *  which is at least as good.
     */
    int BestAssignment(vector<int>& tasks) {
        if (tasks.size() & 1 || tasks.size() == 0)
            throw std::invalid_argument("");

        int ans = -1;
        std::sort(tasks.begin(), tasks.end());
        for (int i = 0, j = tasks.size() - 1; i < j;) {
            ans = max(ans, tasks[i++] + tasks[j--]);
        }
        return ans;
    }
};
