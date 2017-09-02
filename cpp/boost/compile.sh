export LD_LIBRARY_PATH=/opt/x-code/3rd/boost_1_62_0/lib/:$LD_LIBRARY_PATH
#g++ -g -Wall -o tfunc tfunc.cpp -I /opt/x-code/3rd/boost_1_62_0/include/
#g++ -g -Wall -std=c++11 -o traii traii.cpp -I /opt/x-code/3rd/boost_1_62_0/include/
#g++ -g -Wall -std=c++11 -o tsmartptr tsmartptr.cpp -I /opt/x-code/3rd/boost_1_62_0/include/
#g++ -g -Wall -std=c++11 -o tsignal tsignal.cpp -I /opt/x-code/3rd/boost_1_62_0/include/
g++ -g -Wall -std=c++11 -o tlocale tlocale.cpp -I /opt/x-code/3rd/boost_1_62_0/include/ -L /opt/x-code/3rd/boost_1_62_0/lib -lboost_regex

