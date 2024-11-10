all: linked_list dlist

linked_list: linked_list.c linked_list.h
	gcc -Wall -g $< -o $@

dlist: doubly_linked_list.c
	gcc -Wall -g doubly_linked_list.c -o dlist

runDlist: dlist
	./dlist

runLinkedList:
	./linked_list

clean:
	rm -f linked_list
	rm -f dlist