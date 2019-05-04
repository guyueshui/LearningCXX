// 754. Reach a Number


/*
 * Let opt(target) denotes the minimum number of steps
 * required to reach teh dest.
 * Condition on the first step:
 *     1) move 1 step right, then 1 + opt(target - 1)
 *     2) 1 step left, then 1 + opt(target + 1)
 * and base case:
 *     1) opt(0) = 0
 *     2) opt(-1) = opt(1) = 1
 */
