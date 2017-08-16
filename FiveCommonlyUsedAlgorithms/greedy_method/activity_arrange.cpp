/*
 *   活动安排问题
 *   使用贪心法解决
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct ActivityTime {
        ActivityTime(int start, int end) 
            : _start(start), _end(end) {
            }

        ActivityTime() 
            : _start(0), _end(0) {
            }

        friend bool operator<(const ActivityTime& lat, const ActivityTime& rat) {
            return lat._end < rat._end;
        }

        int _start;
        int _end;
};

class ActivityArrange {
    public:

        ActivityArrange(const std::vector<ActivityTime>& v_timelist) {
            _v_time_list = v_timelist;
            _count = v_timelist.size();
            _v_select_flag.resize(_count, false);
        }

        void greedy_selector() {
            __sort_time();
            _v_select_flag[0] = true;
            int j = 0;
            for (int i = 1; i < _count; ++i) {
                if (_v_time_list[i]._start > _v_time_list[i]._end) {
                    _v_select_flag[i] = true;
                    j = i;
                }
            }

            copy(_v_select_flag.begin(), _v_select_flag.end(), std::ostream_iterator<bool>(std::cout, " "));
            std::cout << std::endl;
        }

    private:
        void __sort_time() {
            sort(_v_time_list.begin(), _v_time_list.end());
            for (std::vector<ActivityTime>::iterator iter = _v_time_list.begin();
                    iter != _v_time_list.end();
                    ++iter) {
                std::cout << iter->_start << ", " << iter->_end << std::endl;
            }
        }

    private:
        std::vector<ActivityTime> _v_time_list;
        std::vector<bool> _v_select_flag;
        int _count;
};

int main()
{
    std::vector<ActivityTime> v_activity_timelist;
    v_activity_timelist.push_back(ActivityTime(1, 4));
    v_activity_timelist.push_back(ActivityTime(3, 5));
    v_activity_timelist.push_back(ActivityTime(0, 6));
    v_activity_timelist.push_back(ActivityTime(5, 7));
    v_activity_timelist.push_back(ActivityTime(3, 8));
    v_activity_timelist.push_back(ActivityTime(5, 9));
    v_activity_timelist.push_back(ActivityTime(6, 10));
    v_activity_timelist.push_back(ActivityTime(8, 11));
    v_activity_timelist.push_back(ActivityTime(8, 12));
    v_activity_timelist.push_back(ActivityTime(2, 13));
    v_activity_timelist.push_back(ActivityTime(12, 14));

    ActivityArrange aa(v_activity_timelist);
    aa.greedy_selector();


    return 0;
}

