#--
# SZaru: Porting of excellent Sawzall aggregators. 
#++
#:include:overview.rd


# SZaru namespace
module SZaru
  # Statistical estimators for the total number of unique data items.
  class UniqueEstimator
    # Create a UniqueEstimator object.
    #
    # _max_elems_ is a tuning parameter.
    # If _max_elems_ is bigger, the estimation becomes more accurate but consuming more memory.
    def initialize(max_elems)
      # (native code)
    end

    # Add a new element to this entry.
    # _element_ must be String object.
    def add_elem(elem)
      # (native code) 
    end

    # Return the stimation the number of unique entries.
    def estimate
      # (native code) 
    end
  end # UniqueEstimator

  # Statistical samplings that record the 'top N' data items.
  module TopEstimator
    # TopEstimator of that weight is int32
    class Int32
      # Create a TopEstimator::Int32 object.
      #
      # _top_elems_ is a number of top elements to be estimate.
      def initialize(top_elems)
        # (native code)
      end
      
      # Add a new element to this entry.
      # _element_ must be String object.
      def add_elem(elem)
        # (native code)
      end

      # Add a new weighted element to this entry.
      # _element_ must be String object. 
      # _weight_ msut be Fixnum object.
      def add_weighted_elem(elem, weight)
        # (native code)
      end

      # Return a top elements with weight.
      # Example: [["abc", 7], ["def", 3]]
      def estimate
        # (native code)
      end
    end # Int32

    # TopEstimator of that weight is int64
    class Int64
      # Create a TopEstimator::Int64 object.
      #
      # _top_elems_ is a number of top elements to be estimate.
      def initialize(top_elems)
        # (native code)
      end
      
      # Add a new element to this entry.
      # _element_ must be String object.
      def add_elem(elem)
        # (native code)
      end

      # Add a new weighted element to this entry.
      # _element_ must be String object. 
      # _weight_ msut be Fixnum object.
      def add_weighted_elem(elem, weight)
        # (native code)
      end

      # Return a top elements with weight.
      # Example: [["abc", 7], ["def", 3]]
      def estimate
        # (native code)
      end 
    end # Int64

    # TopEstimator of that weight is Double
    class Double
      # Create a TopEstimator::Double object.
      #
      # _top_elems_ is a number of top elements to be estimate.
      def initialize(top_elems)
        # (native code)
      end
      
      # Add a new element to this entry.
      # _element_ must be String object.
      def add_elem(elem)
        # (native code)
      end

      # Add a new weighted element to this entry.
      # _element_ must be String object. 
      # _weight_ msut be Float object.
      def add_weighted_elem(elem, weight)
        # (native code)
      end

      # Return a top elements with weight.
      # Example: [["abc", 7.0], ["def", 3.0]]
      def estimate
        # (native code)
      end
    end # Double
  end # TopEstimator

  # Approximate N-tiles for data items from an ordered domain.
  module QuantileEstimator
    # TopEstimator of that element is int32
    class Int32
      # Create a QuantileEstimator::Int32 object.
      #
      # _num_quantiles_ is a number of tiles to be estimate.
      def initialize(num_quantiles)
        # (native code)
      end

      # Add a new element to this entry.
      # _element_ must be Fixnum object.
      def add_elem(elem)
        # (native code)
      end

      # Return a estimated N tiles.
      # Example: [0, 3, 7, 9]
      def estimate()
        # (native code)
      end
    end # Int32

    # TopEstimator of that element is int64
    class Int64
      # Create a QuantileEstimator::Int64 object.
      #
      # _num_quantiles_ is a number of tiles to be estimate.
      def initialize(num_quantiles)
        # (native code)
      end

      # Add a new element to this entry.
      # _element_ must be Fixnum object.
      def add_elem(elem)
        # (native code)
      end

      # Return a estimated N tiles.
      # Example: [0, 3, 7, 9]
      def estimate()
        # (native code)
      end
    end # Int64

    # TopEstimator of that element is double
    class Double
      # Create a QuantileEstimator::Double object.
      #
      # _num_quantiles_ is a number of tiles to be estimate.
      def initialize(num_quantiles)
        # (native code)
      end

      # Add a new element to this entry.
      # _element_ must be Fixnum object.
      def add_elem(elem)
        # (native code)
      end

      # Return a estimated N tiles.
      # Example: [0.0, 3.2, 6.8, 9.5]
      def estimate()
        # (native code)
      end
    end # Double
  end # QuantileEstimator
end # SZaru
