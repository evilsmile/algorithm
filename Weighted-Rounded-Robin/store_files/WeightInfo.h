#ifndef __MODEL_WEIGHT_INFO_H__
#define __MODEL_WEIGHT_INFO_H__

#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

namespace models
{
    template<typename T>
    class WeightInfo ;

    template<typename T>
    bool sortDataByWeight(std::vector<WeightInfo<T> >& allWeightInfo, std::vector<T>& vecSortedOut);

    template<typename T>
    std::ostream& operator<<(std::ostream& os, WeightInfo<T>& obj) 
    {
        //TODO::如果obj.m_data没有重载operator<< ?
        os << "data: " << obj.m_data 
            << " weight: " << obj.m_iWeight
            << " current_weight: " << obj.m_iCurrentWeight
            << " effective_weight: " << obj.m_iEffectiveWeight;

        return os;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class WeightInfo 
    {
        friend bool sortDataByWeight<T>(std::vector<WeightInfo<T> >& allWeightInfo, std::vector<T>& vecSortedOut);
        friend std::ostream& operator<< <> (std::ostream& os, WeightInfo<T>& obj) ;
        public:
            WeightInfo(const T& data, int iWeight);
            WeightInfo& operator=(const WeightInfo<T>& other);
            WeightInfo(const WeightInfo<T>& other);

        public:
            T m_data;

        private:
            int m_iWeight;
            int m_iCurrentWeight;
            int m_iEffectiveWeight;

        private:

            class WeightSort 
            {
                public:
                    bool operator()(const WeightInfo<T>& l, const WeightInfo<T>& r) {
                        return l.m_iCurrentWeight > r.m_iCurrentWeight;
                    }
            };
    };

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    WeightInfo<T>::WeightInfo(const T& data, int iWeight)
        : m_data(data),
        m_iWeight(iWeight),
        m_iCurrentWeight(0),
        m_iEffectiveWeight(iWeight)
    {
    }

    template<typename T>
    WeightInfo<T>::WeightInfo(const WeightInfo<T>& other)
        : m_data(other.m_data),
        m_iWeight(other.m_iWeight),
        m_iCurrentWeight(other.m_iCurrentWeight),
        m_iEffectiveWeight(other.m_iEffectiveWeight)
    {
    }

    template<typename T>
    WeightInfo<T>& WeightInfo<T>::operator=(const WeightInfo<T>& other)
    {
        this->m_data = other.m_data; 
        this->m_iWeight = other.m_iWeight; 
        this->m_iCurrentWeight = other.m_iCurrentWeight; 
        this->m_iEffectiveWeight = other.m_iEffectiveWeight; 

        return *this;
    }

#define DEBUG_WEIGHTINFO
#ifdef DEBUG_WEIGHTINFO
#define DEBUG_OUTPUT(msg, allWeightInfo) \
        std::cout << msg << ": " << std::endl;  \
        for (size_t i = 0; i < allWeightInfo.size(); ++i) {  \
            std::cout << allWeightInfo[i] << std::endl;  \
        }
#else
#define DEBUG_OUTPUT(msg, allWeightInfo) 
#endif

    template<typename T>
    bool sortDataByWeight(std::vector<WeightInfo<T> >& allWeightInfo, std::vector<T>& vecSortedOut)
    {
        if (allWeightInfo.size() == 0) {
            return false;
        }

        int total = 0;

        DEBUG_OUTPUT("Before add: ", allWeightInfo);
        // 以有效权重更新当前权重
        typename std::vector<WeightInfo<T> >::iterator iter;
        for (iter = allWeightInfo.begin(); iter != allWeightInfo.end(); ++iter) {
            iter->m_iCurrentWeight += iter->m_iEffectiveWeight;
            total += iter->m_iEffectiveWeight;
        }

        DEBUG_OUTPUT("Before sort: ", allWeightInfo);

        // 按当前权重排序,高的在前面
        std::sort(allWeightInfo.begin(), allWeightInfo.end(), typename WeightInfo<T>::WeightSort());

        DEBUG_OUTPUT("AFter sort: ", allWeightInfo);
 
        // 权重最高的减去total，以便下次选择时给其它候选者机会
        allWeightInfo[0].m_iCurrentWeight -= total;

        DEBUG_OUTPUT("AFter sub: ", allWeightInfo);

        vecSortedOut.clear();

        // 把权重信息中的通道组号塞到结果集中
        for (iter = allWeightInfo.begin(); iter != allWeightInfo.end(); ++iter) {
            vecSortedOut.push_back(iter->m_data);
        }

        return true;
    }
}

#endif
