# import package
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# environment arg

scale = 150
learning_rate = 0.001

# load data and set 總成績 as prediction
# input 10 channel, output 1 channel

df = pd.read_csv('Data.csv') / scale
train_sol = np.array(df['總成績']).T
df = df.drop('總成績', axis=1)
train_in = np.array(df)

# initialize nn_weights

np.random.seed(1)

nn_weights1 = 2 * np.random.random((10,1)) - 1
nn_weights2 = 2 * np.random.random((10,1)) - 1
nn_weights3 = 2 * np.random.random((1,1)) - 1
nn_weights4 = 2 * np.random.random((1,1)) - 1

loss = []

# train the network

for i in range(10000):
    
    # sigmoid
    train_out1 = ( 1 / (1 + np.exp(-(np.dot(train_in, nn_weights1)))) )
    train_out2 = ( 1 / (1 + np.exp(-(np.dot(train_in, nn_weights2)))) )
    train_add_out = np.dot(train_out1, nn_weights3) + np.dot(train_out2, nn_weights4)
    train_out3 = ( 1 / (1 + np.exp(-train_add_out)) )

    aloss = np.square(np.subtract(train_sol, train_out3.T)).mean()
    loss.append(aloss)
    print(aloss)

    nn_weights3 += np.dot(train_out1.T, (train_sol - train_out3.T).T * train_add_out * (1 - train_add_out)) * learning_rate 
    nn_weights4 += np.dot(train_out2.T, (train_sol - train_out3.T).T * train_add_out * (1 - train_add_out)) * learning_rate 
    nn_weights1 += np.dot(train_in.T, (train_sol - train_out3.T).T * train_add_out * (1 - train_add_out) * nn_weights3 * train_out1 * (1 - train_out1)) * learning_rate 
    nn_weights2 += np.dot(train_in.T, (train_sol - train_out3.T).T * train_add_out * (1 - train_add_out) * nn_weights4 * train_out2 * (1 - train_out2)) * learning_rate 
    
# test

test_in = np.array([11,86,90,93.5,93,90.63,90,99,106,98.33]) / scale
test_out1 = ( 1 / (1 + np.exp(-(np.dot(test_in, nn_weights1)))) )
test_out2 = ( 1 / (1 + np.exp(-(np.dot(test_in, nn_weights2)))) )
test_add_out = np.dot(test_out1, nn_weights3) + np.dot(test_out2, nn_weights4)
test_out3 = ( 1 / (1 + np.exp(-test_add_out)) )
print(test_out3 * scale)
print(np.square(np.subtract(train_sol, test_out3.T)).mean())

