class UniqueEstimator:
    """
    Statistical estimators for the total number of unique data items.
    """

    def __init__(self, max_elems):
        """
        Create a UniqueEstimator object.
        @type  max_elems: number
        @param max_elems: Tuning parameter. If _max_elems_ is bigger,
        the estimation becomes more accurate but consuming more memory.
        """
        pass

    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: str
        @param elem: The element to be add
        """
        pass

    def estimate(self):
        """
        Return the estimation the number of unique entries.
        @rtype:  number
        @return: the number of unique entries
        """
        pass

class TopEstimatorInt32:
    """
    Statistical samplings that record the 'top N' data items.
    TopEstimator of that weight is int32
    """
    def __init__(self, top_elems):
        """
        Create a TopEstimatorInt32 object.
        @type  top_elems: number
        @param top_elems: Number of top elements to be estimate.
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: str
        @param elem: The string element to be add
        """
        pass

    def add_weighted_elem(self, elem, weight):
        """
        Add a new weighted element to this entry.
        @type  elem: str
        @param elem: The string element to be add.
        
        @type  weight: number
        @param weight: The int weight of element.
        """
        pass

    def estimate(self):
        """
        Return a top elements with weight.
        Example: [["abc", 7], ["def", 3]]
        @rtype: list
        @return: top elements
        """
        pass

    
class TopEstimatorInt64:
    """
    Statistical samplings that record the 'top N' data items.
    TopEstimator of that weight is int64
    """
    def __init__(self, top_elems):
        """
        Create a TopEstimatorInt64 object.
        @type  top_elems: number
        @param top_elems: Number of top elements to be estimate.
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: str
        @param elem: The string element to be add
        """
        pass

    def add_weighted_elem(self, elem, weight):
        """
        Add a new weighted element to this entry.
        @type  elem: str
        @param elem: The string element to be add.
        
        @type  weight: number
        @param weight: The int weight of element.
        """
        pass

    def estimate(self):
        """
        Return a top elements with weight.
        Example: [["abc", 7], ["def", 3]]
        @rtype: list
        @return: top elements
        """
        pass


class TopEstimatorDouble:
    """
    Statistical samplings that record the 'top N' data items.
    TopEstimator of that weight is double
    """
    def __init__(self, top_elems):
        """
        Create a TopEstimatorDouble object.
        @type  top_elems: number
        @param top_elems: Number of top elements to be estimate.
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: str
        @param elem: The string element to be add
        """
        pass

    def add_weighted_elem(self, elem, weight):
        """
        Add a new weighted element to this entry.
        @type  elem: str
        @param elem: The string element to be add.
        
        @type  weight: float
        @param weight: The int weight of element.
        """
        pass

    def estimate(self):
        """
        Return a top elements with weight.
        Example: [["abc", 7.0], ["def", 3.0]]
        @rtype: list
        @return: top elements
        """
        pass


class QuantileEstimatorInt32:
    """
    Approximate N-tiles for data items from an ordered domain.
    QuantileEstimator of that weight is int32
    """
    def __init__(self, quantile_elems):
        """
        Create a QuantileEstimatorInt32 object.
        @type  quantile_elems: number
        @param quantile_elems: Number of tiles to be estimate
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: number
        @param elem: The element to be add
        """
        pass

    def estimate(self):
        """
        Return a estimated N tiles.
        Example: [0, 3, 7, 9]
        @rtype: list
        @return: n-tiles
        """
        pass


class QuantileEstimatorInt64:
    """
    Approximate N-tiles for data items from an ordered domain.
    QuantileEstimator of that weight is int64
    """
    def __init__(self, quantile_elems):
        """
        Create a QuantileEstimatorInt64 object.
        @type  quantile_elems: number
        @param quantile_elems: Number of tiles to be estimate
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: number
        @param elem: The element to be add
        """
        pass

    def estimate(self):
        """
        Return a estimated N tiles.
        Example: [0, 3, 7, 9]
        @rtype: list
        @return: n-tiles
        """
        pass


class QuantileEstimatorDouble:
    """
    Approximate N-tiles for data items from an ordered domain.
    QuantileEstimator of that weight is double
    """
    def __init__(self, quantile_elems):
        """
        Create a QuantileEstimatorDouble object.
        @type  quantile_elems: number
        @param quantile_elems: Number of tiles to be estimate
        """
        pass


    def add_elem(self, elem):
        """
        Add a new element to this entry.
        @type  elem: float
        @param elem: The element to be add
        """
        pass

    def estimate(self):
        """
        Return a estimated N tiles.
        Example: [0.0, 3.0, 7.0, 9.0]
        @rtype: list
        @return: n-tiles
        """
        pass
