#include <iostream>
#include "OfficeHour.h"

/*
Given the current Office Hour queue and the currently on-duty staffers, return
how long the nth student will need to wait before a Staffer can reach them
Return -1 if there are no staff available to help the nth student

@param queue A queue containing the students currently waiting for help
@param onDutyStaff  A vector of Staffers currently on duty
@param nthStudent   The student for whom we are calculating a wait time
@return             How many minutes the nth student will have to wait before getting help
*/
int waitTime(queue<Student> queue, vector<Staffer> onDutyStaff, int nthStudent) {
    // Your code here!
    int answer = -1;

    // Basic Test - No Staff On Duty
    if (onDutyStaff.size() == 0) {
    	return -1;
    }
    
    vector<int> staffTime;
    vector<bool> staffAvailbility;
    for(auto s: onDutyStaff){
      staffAvailbility.push_back(true);
      staffTime.push_back(0);
    }

    // Student curr_stu = queue.front();
    // while(count < nthStudent){
    //
    // }

    //test cases

    // Basic Test - One Staff On Duty

    // Basic Test - Two Staff On Duty

    // Basic Test - Tired Staff On Duty

    // Test - Three Staff On Duty

    // Test - Long Queue, Long Day

    // Sneaky - One Tired Staff On Duty

    // Super Sneaky - Long night, Monday morning

    return answer;
}
