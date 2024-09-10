use std::collections::HashMap;

struct Solution {}

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut map: HashMap<i32, usize> = HashMap::with_capacity(nums.len());
        for (i, &num) in nums.iter().enumerate() {
            if let Some(&it) = map.get(&(target - num)) {
                if i != it {
                    return vec![i as i32, it as i32];
                }
            }
            map.insert(num, i);
        }
        vec![]
    }
}
