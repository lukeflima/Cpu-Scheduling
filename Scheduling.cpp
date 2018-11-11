#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>

std::stringstream output;

class Process{
public:
    int m_ID;
    double t_duration, t_returning, t_arrival, t_wait, t_response, t_ran, t_finished;
    Process(int ID, double arrival, double duration){
        m_ID = ID;
        t_arrival = arrival;
        t_duration = duration;
        t_response = t_returning = t_finished = t_ran = t_wait = 0;
    }
};

void clean(std::vector<Process*> p){
    for (auto& p1: p) p1->t_response = p1->t_returning = p1->t_finished = p1->t_ran = p1->t_wait = 0;

}

void fcfs(std::vector<Process*> p){
    std::sort(p.begin(), p.end(), [](const Process*  a, const Process*  b) -> bool{ return a->t_arrival < b->t_arrival; });

    double wait = 0;
    for (auto& p1: p){
        if(p1->t_arrival > wait) wait += p1->t_arrival - wait;
        p1->t_ran = p1->t_duration;
        p1->t_response = p1->t_wait = wait - p1->t_arrival;
        wait += p1->t_ran;
    }

    for(auto& p1: p) p1->t_returning = p1->t_duration + p1->t_wait;

    double mean_wait = 0, mean_return = 0, mean_response = 0, sum_of_elems = 0;

    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_wait; });
    mean_wait = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_returning; });
    mean_return = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_response; });
    mean_response = sum_of_elems/p.size();

    std::cout << "FCFS " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    output << "FCFS " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    clean(p);
}

void sjf(std::vector<Process*> p){
    std::vector<Process*> v(p);
    double wait = 0;
    int i =0;

    while(v.size()){
        std::sort(v.begin(), v.end(), [](const Process*  a, const Process*  b) -> bool{ return a->t_duration < b->t_duration; });

        for (auto& p1: v){
            if(wait >= p1->t_arrival){
                p1->t_ran = p1->t_duration;
                p1->t_response = p1->t_wait = wait - p1->t_arrival;
                wait += p1->t_ran;
                v.erase(v.begin() + i);
                break;
            }
            i++;
        }
        i=0;
    }

    for(auto& p1: p) p1->t_returning = p1->t_duration + p1->t_wait;

    double mean_wait = 0, mean_return = 0, mean_response = 0, sum_of_elems = 0;

    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_wait; });
    mean_wait = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_returning; });
    mean_return = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_response; });
    mean_response = sum_of_elems/p.size();

    std::cout << "SJF " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    output << "SJF " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    clean(p);
}

void rr(std::vector<Process*> p){
    std::sort(p.begin(), p.end(), [](const Process*  a, const Process*  b) -> bool{ return a->t_arrival < b->t_arrival; });

    std::queue<Process*> q;
    int wait = -2;
    int count = 0, count2 = 0;

    bool *calculated_reponse = new bool[p.size()];
    for(auto i = 0; i< p.size(); i++) calculated_reponse[i] = false;

    bool *inQueue = new bool[p.size()];
    for(auto i = 0; i< p.size(); i++) inQueue[i] = false;

    Process *p1;
    int sizeOfLastQueue = 0;
    while(1){
        sizeOfLastQueue = q.size();
        if(!q.empty()){
            p1 = q.front();
            q.pop();

            if(!calculated_reponse[p1->m_ID]){
                p1->t_response = wait - p1->t_arrival - p1->t_wait - p1->t_ran ;
                calculated_reponse[p1->m_ID] = true;
            }

            if(sizeOfLastQueue) p1->t_wait +=  wait - p1->t_arrival - p1->t_wait - p1->t_ran ;
            p1->t_ran +=2;
        }

        wait +=2;

         for(auto i = 0; i < p.size() ; i++){
            bool help = ((wait >= p[i]->t_arrival )  && !inQueue[i]);
            if(help){
                q.push(p[i]);
                inQueue[i] = true;
            }
            if(p[i]->t_ran >= p[i]->t_duration)  count++;
        }

        if(count == p.size()) break;
        count = 0;
        if(p1 && p1->t_ran < p1->t_duration)  q.push(p1);


    }

    for(auto& p1: p) p1->t_returning = p1->t_duration + p1->t_wait;

    double mean_wait = 0, mean_return = 0, mean_response = 0, sum_of_elems = 0;

    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_wait; });
    mean_wait = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_returning; });
    mean_return = sum_of_elems/p.size();

    sum_of_elems = 0;
    std::for_each(p.begin(), p.end(), [&] (Process* p) { sum_of_elems += p->t_response; });
    mean_response = sum_of_elems/p.size();

    std::cout << "RR " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    output << "RR " << mean_return << " " << mean_response << " " << mean_wait << std::endl;
    clean(p);
}

int main(int argc, char **argv){
    std::vector<Process*> processes;

    double temp1 = -1, temp2 = -1;
    Process *p;
    int i = 0;
    std::fstream f("input.txt",  std::ifstream::in);

    while(!f.eof()){
            f >> temp1 >> temp2;
        if( temp1 >= 0 && temp2 >= 0){
            p = new Process(i++,temp1, temp2);
            processes.push_back(p);
        }
        temp1 = temp2 = -1;
    }

    fcfs(processes);
    sjf(processes);
    rr(processes);

    for (auto& p: processes){
        delete p;
    }
    std::ofstream out("output.txt", std::ofstream::out);
    out << output.str();
}