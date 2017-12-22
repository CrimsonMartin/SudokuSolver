make
echo "client1"
./client 127.0.0.1 8000 puzzle1.txt
echo "client2"
./client 127.0.0.1 8001 puzzle2.txt
echo "client3"
./client 127.0.0.1 8002 puzzle3.txt
echo "client4"
./client 127.0.0.1 8003 puzzle4.txt
echo "client5"
./client 127.0.0.1 8004 puzzle5.txt
