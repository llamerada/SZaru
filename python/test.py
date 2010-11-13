import szaru
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
    qtl_est = szaru.QuantileEstimatorInt32(11)
    
    lst = range(1001)
    random.shuffle(lst)
    for i in lst:
        qtl_est.add_elem(i)
        
    print qtl_est.estimate()

test_unique()
test_top()
test_quantile()


    

