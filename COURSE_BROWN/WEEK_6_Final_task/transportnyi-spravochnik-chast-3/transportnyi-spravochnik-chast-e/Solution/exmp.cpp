graph initialize_graph(Stops_Buses & sab){
   graph result(sab.stops.size()*2);
   set<string> set_of_stops;
   size_t index = 0;
   for(auto &bus: sab.buses){
       vector<pair<size_t,vector<double>>> time_of_bus_ridings;
       Stop_info prev = sab.get_stop(*bus.second.stops.begin());
       string round_name = prev.name;
       if(set_of_stops.count(prev.name)==0){
           result.AddEdge({prev.start_waiting,prev.stop_waiting,sab.settings.bus_wait_time,EDGE_TYPE::WAIT,prev.name,index});
           set_of_stops.insert(prev.name);
       }
       for(auto it_stop = bus.second.stops.begin() + 1; it_stop != bus.second.stops.end(); it_stop++){
           Stop_info cur = sab.get_stop(*it_stop);
           if(set_of_stops.count(cur.name)==0){
               result.AddEdge({cur.start_waiting,cur.stop_waiting,sab.settings.bus_wait_time,EDGE_TYPE::WAIT,cur.name,index});
               set_of_stops.insert(cur.name);
           }
           double time_of_bus_riding;
           if(prev.dis_to.count(cur.name) != 0){
               time_of_bus_riding = ((prev.dis_to.at(cur.name)/1000)/sab.settings.bus_velocity)*60;
           }else{
               time_of_bus_riding = ((cur.dis_to.at(prev.name)/1000)/sab.settings.bus_velocity)*60;
           }
           vector<double> new_vec;
           time_of_bus_ridings.push_back(make_pair(prev.stop_waiting,move(new_vec)));
           for(auto &i: time_of_bus_ridings){
               i.second.push_back(time_of_bus_riding);
           }
           for(auto &i: time_of_bus_ridings){
               double a = accumulate(i.second.begin(),i.second.end(),0.0);
               double time_of_bus_riding_all= a;
               result.AddEdge({i.first,cur.start_waiting,time_of_bus_riding_all,EDGE_TYPE::BUS,bus.second.name,index});
           }
           prev = cur;
       }
       if(bus.second.round  != 1){
           vector<pair<size_t,vector<double>>> time_of_bus_ridings;
           vector<string> stops_2 = bus.second.stops;
           reverse(stops_2.begin(),stops_2.end());
           Stop_info prev = sab.get_stop(*stops_2.begin());
           if(set_of_stops.count(prev.name)==0){
               result.AddEdge({prev.start_waiting,prev.stop_waiting,sab.settings.bus_wait_time,EDGE_TYPE::WAIT,prev.name,index});
               set_of_stops.insert(prev.name);
           }
           for(auto it_stop = stops_2.begin() + 1; it_stop != stops_2.end(); it_stop++){
               Stop_info cur = sab.get_stop(*it_stop);
               double time_of_bus_riding;
               vector<double> new_vec;
               time_of_bus_ridings.push_back(make_pair(prev.stop_waiting,move(new_vec)));
               for(auto &i: time_of_bus_ridings){
                   i.second.push_back(time_of_bus_riding);
               }
               for(auto &i: time_of_bus_ridings){
                   double time_of_bus_riding_all= accumulate(i.second.begin(),i.second.end(),0.0);
                   result.AddEdge({i.first,cur.start_waiting,time_of_bus_riding_all,EDGE_TYPE::BUS,bus.second.name,index});
               }
               prev = cur;
           }

       }
       index++;
   }
   return result;
}
