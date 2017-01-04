//Ride to School
//
// Description
//
// Many graduate students of Peking University are living in Wanliu
// Campus, which is 4.5 kilometers from the main campus –
// Yanyuan. Students in Wanliu have to either take a bus or ride a
// bike to go to school. Due to the bad traffic in Beijing, many
// students choose to ride a bike.
//
// We may assume that all the students except "Charley" ride from
// Wanliu to Yanyuan at a fixed speed. Charley is a student with a
// different riding habit – he always tries to follow another rider to
// avoid riding alone. When Charley gets to the gate of Wanliu, he
// will look for someone who is setting off to Yanyuan. If he finds
// someone, he will follow that rider, or if not, he will wait for
// someone to follow. On the way from Wanliu to Yanyuan, at any time
// if a faster student surpassed Charley, he will leave the rider he
// is following and speed up to follow the faster one.
//
// We assume the time that Charley gets to the gate of Wanliu is
// zero. Given the set off time and speed of the other students, your
// task is to give the time when Charley arrives at Yanyuan.
//
//  Input
//
//  There are several test cases. The first line of each case is N (1
//  <= N <= 10000) representing the number of riders (excluding
//  Charley). N = 0 ends the input. The following N lines are
//  information of N different riders, in such format:
//
//    Vi [TAB] Ti
//
//    Vi is a positive integer <= 40, indicating the speed of the i-th
//    rider (kph, kilometers per hour). Ti is the set off time of the
//    i-th rider, which is an integer and counted in seconds. In any
//    case it is assured that there always exists a nonnegative Ti.
//
//    Output
//
//    Output one line for each case: the arrival time of
//    Charley. Round up (ceiling) the value when dealing with a
//    fraction.

#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
///////////////////////////////////////////////////////

typedef std::pair<float, float> bike_t; // velocity in m/s and initial pos
typedef std::vector< bike_t > bikes_vec_t;


// return tim of interception
float calc_time_intercept(bike_t bike1, bike_t bike2)
{
  return (bike1.second - bike2.second) / (bike2.first - bike1.first);
}
  

//
bool find_next_bike_intercept(bikes_vec_t::iterator begin, bikes_vec_t::iterator end, bike_t &charley, float &charley_pos, float final_destination)
{
  //std::cout << "Finding next intercept Charley pos: " << charley_pos << ". Charley vector vel: " << charley.first << " + e0: " << charley.second << std::endl;
  float min_t(1000000);
  float min_pos(0);
  bikes_vec_t::iterator min_bike;
  bool found(false);
  
  for (bikes_vec_t::iterator it = begin; it != end; ++it) {
    float t_intercept = calc_time_intercept(*it, charley);
    float pos = (*it).first * t_intercept + (*it).second;
    
    //std::cout << "Interception with vel: " << it->first << "+ e0: " << it->second << ". t= " << t_intercept << ". pos = " << pos << std::endl;

    if ((pos >= charley_pos) && (pos < final_destination) && ((*it).first > charley.first) ) {
      if ((t_intercept >=0) && (t_intercept <= min_t)) {
        min_t = t_intercept;
        min_pos = pos;
        min_bike = it;
        found = true;
      }
    }
    
  }

  if (found) {
    charley = *min_bike;
    charley_pos = min_pos;
  }
  return found;
}

int main(void) {
  unsigned int N;
  const unsigned int TOTAL_DISTANCE = 4500; // meters
  while (std::cin >> N) {
    if (N==0) return 0;

    // read N bikes info
    bikes_vec_t bikes;
    bike_t charley(0,0);
    float charley_pos=0;
    
    for (unsigned int i=0; i<N; i++) {
      float vel, t0, initial_pos;
      std::cin >> vel >> t0;

      // change vel from km/h to m/s
      vel = vel * (1000.0/3600.0);
      initial_pos = - vel * t0;
        
      bikes.push_back(std::make_pair(vel,initial_pos));
    }

    // Loop thru bikes until we reach the final_destination
    while(1) {
      if (!find_next_bike_intercept(bikes.begin(), bikes.end(), charley, charley_pos, TOTAL_DISTANCE)) {
        // arrive to final destination. Return the time
        std::cout <<  ceil((TOTAL_DISTANCE - charley.second) / charley.first) << std::endl;
        break;
      }
        
      
    }

    
  }


}
