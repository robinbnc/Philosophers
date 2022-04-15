#!/bin/bash
blue=$(tput setaf 4)
normal=$(tput sgr0)
RED=$(tput setaf 1)

actions() {
   timeout 30 ./philo $1 $2 $3 $4 $5  
}

echo -e "<-- test 1 800 200 200 -->\n"
i=0;
while [ $i -ne 10 ]; do
   actions 1 800 200 200 > /dev/null
   if [ $? -eq 0 ]
   	then
	   echo -n "${blue}OK ${normal}"
	else
	   echo -n "${RED}KO ${normal}"
	fi
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 5 800 200 200 -->\n"
i=0;
while [ $i -ne 10 ]; do
   actions 5 800 200 200 > /dev/null;
   if [ $? -ne 0 ]
   	then
	   echo -n "${blue}OK ${normal}"
	else
	   echo -n "${RED}KO ${normal}"
	fi
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 5 800 200 200 7-->\n"
i=0;
while [ $i -ne 10 ]; do
   ret=`actions 5 800 200 200 7 | grep "1 is eating" | wc -l`;
   if [ $ret -eq 7 ]
   	then
	   echo -n "${blue}OK ${normal}"
	else
	   echo -n "${RED}KO ${normal}"
	fi
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 4 410 200 200 -->\n"
i=0;
while [ $i -ne 10 ]; do
   actions 4 410 200 200  > /dev/null;
   if [ $? -ne 0 ]
   	then
	   echo -n "${blue}OK ${normal}"
	else
	   echo -n "${RED}KO ${normal}"
	fi
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 4 310 200 100 -->\n"
i=0;
while [ $i -ne 20 ]; do
   actions 4 310 200 100 > /dev/null;
   if [ $? -eq 0 ]
   	then
	   echo -n "${blue}OK ${normal}"
	else
	   echo -n "${RED}KO ${normal}"
	fi
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 2 310 200 100 -->\n"
i=0;
while [ $i -ne 50 ]; do
   ret=`actions 2 310 200 100 | grep died | cut -d' ' -f1`
   echo -n "$ret ";
   ((i=i+1))
done
echo -e "\n";

echo -e "<-- test 2 310 200 400 -->\n"
i=0;
while [ $i -ne 50 ]; do
   ret=`actions 2 310 200 100 | grep died | cut -d' ' -f1`
   echo -n "$ret ";
   ((i=i+1))
done
echo -e "\n";
