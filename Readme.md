#Read me
## Assignment 1

###Inputs
- There are two clients in the assignment1: myClient.c & myClient1.c
- In myClient.c,
  + There are five data inputs and they are all correct.

#Server should be restart at here!!
- In myClient1.c:
  +There are five data inputs. 
    - The first one is the correct one.
    - The second one's length is not correct.
    - The third one does not have endOfPacket.
    - The fourth one is in wrong order.
    - The fifth one is duplicate packet.

- Sever has no response 
  + When server is closed, the client won't receive ack from server. After 3 seconds, it will be timeout.Client will send the packet again.After 3 times. the client will output "server no respond"

### ScreenShots
  + Server.jpg is the screenshot of the server.
  + rightOrder.jpg is the screenshot of the correct order.
  + WrongPacket.jpg is the screenshot of all wrong inputs.
  + NoResponse.jpg is the screenshot of the no response.

## Assignment 2
###Inputs
- Input is in the myClient.c.
  + There are four inputs
    - The first one is correct one.
    - The second one has not paid.
    - The third one's technology is not correct.
    - The fourth one does not exist.

### ScreenShots
  + Sever.jpg is the screenshot of the server.
  + client.jpg is the screenshot of the client.
