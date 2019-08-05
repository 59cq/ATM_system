all:
	gcc server.c msg_queue.c -o server
	gcc client.c msg_queue.c -o client
	gcc open.c msg_queue.c tools.c -o open
	gcc destroy.c msg_queue.c tools.c -o destroy
	gcc unlock.c msg_queue.c tools.c -o unlock
	gcc login.c msg_queue.c tools.c -o login
	gcc query.c msg_queue.c tools.c -o query
	gcc store.c msg_queue.c tools.c -o store
	gcc withdraw.c msg_queue.c tools.c -o withdraw
	gcc transfer.c msg_queue.c tools.c -o transfer
	gcc modpswd.c msg_queue.c tools.c -o modpswd
clean:
	rm server open client destroy unlock login query store withdraw transfer modpswd a.out 