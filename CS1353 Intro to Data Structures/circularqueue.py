max_size = 5
items = []
front = rear = -1

def isEmpty():
    if front == -1 :
        return True

    return False

def isFull():
    if (rear+1)%max_size == front :
        return True
        
    return False  

def Enqueue(element):
    global items, front, rear
    if isFull():
        print('Queue is full!')
        return

    if front == -1 :
        front = 0

    rear = (rear+1)%max_size
    items.insert(rear, element)  
    print("Inserted -> ", element)
        
def Dequeue():
    global items, front, rear
    if isEmpty():
        print('Queue is empty!')
        return

    print("Deleted ->", items[front])
    del items[front]
    if front == rear :
        front = rear = -1

    front = (front+1)%max_size

def printf() :
    i = front
    while i != rear :
        print(items[i], end =' ')
        i = (i+1)%max_size
    print(items[rear], "\n")

Enqueue(0); 
printf();
print(front,  rear)
Enqueue(10); 
printf();
print(front,  rear)
Enqueue(20); 
printf();
print(front,  rear)
Enqueue(72); 
printf();
print(front,  rear)
Enqueue(5); 
printf(); 
print(front,  rear)  
Dequeue();
printf(); 
print(front,  rear)   
Enqueue(22);
printf();
print(front,  rear)
print(items)
Enqueue(200); 
printf();
print(front,  rear)
Dequeue();
printf();
print(front,  rear)

              