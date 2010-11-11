import szaru
import sys
import random

def test_unique():
    ue = szaru.UniqueEstimator(10)
    for i in range(1009):
        ue.add_elem('spam' + str(i))
    print ue.estimate()

def test_top():
    # te = szaru.TopEstimatorDouble(10)
    te = szaru.TopEstimatorInt32(10)
    for i in range(20):
        for j in range(i):
            te.add_elem('spam' + str(i))
    print te.estimate()

def test_quantile():
    # te = szaru.TopEstimatorDouble(10)
    te = szaru.QuantileEstimatorInt32(10)
    lst = []
    for i in range(100):
        lst.append(i)
    random.shuffle(lst)
    for i in lst:
        te.add_elem(i)
    print te.estimate()

test_unique()
test_top()
test_quantile()

    

