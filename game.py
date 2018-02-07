import math
def game_over(matrix):
    if (matrix[0][0]==matrix[1][1])and(matrix[1][1]==matrix[2][2]):
    	if matrix[0][0]==comp_inpt:
        	return -20
        elif matrix[0][0]==usr_inpt:
        	return 20
    if (matrix[0][2]==matrix[1][1])and(matrix[1][1]==matrix[2][0]):
    	if matrix[0][2]==comp_inpt:
        	return -20
        elif matrix[0][2]==usr_inpt:
        	return 20	
    # diagonals checked
    for i in range(3):
    	if(matrix[i][0]==matrix[i][1])and(matrix[i][1]==matrix[i][2]):
        	if matrix[i][0]==comp_inpt:
                	return -20
                elif matrix[i][0]==usr_inpt:
                	return 20  
    # columns checked
    for j in range(3):
    	if(matrix[0][j]==matrix[1][j])and(matrix[1][j]==matrix[2][j]):
        	if matrix[0][j]==comp_inpt:
                	return -20
                elif matrix[0][j]==usr_inpt:
                	return 20 	                       
    # rows checked
    return 0
def move(matrix):
    x=int(input("enter the row no."))
    y=int(input("enter the column no."))
    # elimination of all the wrong inputs
    while (x>3 or x<1 or y<1 or y>3) or matrix[x-1][y-1]!=-1:
        x=int(input("enter the row no."))
        y=int(input("enter the column no."))
    matrix[x-1][y-1]=usr_inpt
    print(matrix[0])
    print(matrix[1])
    print(matrix[2])
    return
def minimax(matrix,depth,usr_turn):
    if game_over(matrix):
    	return game_over(matrix)
    elif depth==9:
        return 0
    # base cases checked
    if usr_turn:
        bestVal=-1000
        for i in range(3):
        	for j in range(3):
                        if matrix[i][j]==-1:
                        	matrix[i][j]=usr_inpt
                                value=minimax(matrix,depth+1,not usr_turn)
        	                bestVal=max(value,bestVal)
                                matrix[i][j]=-1     
        return bestVal
    # computer played others chance to check other moves
    else:
        bestVal=1000
        for i in range(3):
        	for j in range(3):
                        if matrix[i][j]==-1:
                        	matrix[i][j]=comp_inpt
                                value=minimax(matrix,depth+1,not usr_turn)
        	                bestVal=min(value,bestVal)
                                matrix[i][j]=-1  
        return bestVal
    # computer played its chance to check other moves
def bestMove(matrix,depth):
    bestMove = [-1,-1]
    # for the best move
    bestVal=1000
    for i in range(3):
    	for j in range(3):
        	if matrix[i][j]==-1:
                        matrix[i][j]=comp_inpt
                	val=minimax(matrix,depth+1,True)
                        matrix[i][j]=-1
                        if val<bestVal:
                        	bestMove=[i,j]
                                bestVal=val
    return bestMove
# main code 
matrix=[[-1,-1,-1],[-1,-1,-1],[-1,-1,-1]]
usr_inpt=int(input("please choose either 0 or 1"))
if usr_inpt==0 or usr_inpt==1:
    comp_inpt=1-usr_inpt
i=1
while True:
    # user's move
    move(matrix)
    if game_over(matrix)==20:
    	print("Congrats u hve dn impossible!!!")
        break
    elif game_over(matrix)==-20:
    	print("better luck next time")
    	break
    elif i >= 9:
        print("abe draw kya hota h be!!!")
        break
    i=i+1
    # comp's move
    vec=bestMove(matrix,i)
    if vec==[-1,-1]:
    	print("oops!!!")
        break
    else:
        xi,yi=vec[0],vec[1]
    	matrix[xi][yi]=comp_inpt
        print(matrix[0])
        print(matrix[1])
        print(matrix[2])
    if game_over(matrix)==20:
    	print("Congrats u hve dn impossible!!!")
        break
    elif game_over(matrix)==-20:
    	print("better luck next time")
    	break
    elif i >= 9:
        print("abe draw kya hota h be!!!")
        break
    i=i+1
