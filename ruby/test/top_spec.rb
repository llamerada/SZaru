require File.join(File.dirname(__FILE__), "../ext/szaru")

include SZaru
top_estimators = [TopEstimator::Int32, TopEstimator::Int64, TopEstimator::Double]

def convert_value_from_index(index, value)
  case index
  when 0, 1
    value.to_i
  when 2
    value.to_f
  end
end

top_estimators.each_with_index do |top_estimator, te_index|
  describe top_estimator do
    it "return [] if no addition exists" do
      te = top_estimator.new(10)
      te.estimate.should == []
    end

    it "return [] if top_elems is 0" do
      te = top_estimator.new(0)
      te.add_elem("test")
      te.estimate.should == []
    end

    it "return exact number when the number of elements is small than top_elems" do
      te = top_estimator.new(10)
      n_elemnts = 5
      n_elemnts.times do |i|
        te.add_elem("test#{i}")
        te.add_weighted_elem("test#{i}", convert_value_from_index(te_index, i))
      end
      top_elements = te.estimate
      top_elements.length.should == n_elemnts
      n_elemnts.times do |i|
        # check element
        top_elements[i][0].should == "test#{n_elemnts - i - 1}"
        # check weight
        exact_weight = convert_value_from_index(te_index, n_elemnts - i)
        top_elements[i][1].should == exact_weight
      end
    end

    it "return same result when calling estimate twice" do
      te = top_estimator.new(10)
      n_elemnts = 5
      n_elemnts.times do |i|
        te.add_elem("test#{i}")
        te.add_weighted_elem("test#{i}", convert_value_from_index(te_index, i))
      end
      # first call
      top_elements = te.estimate
      # second call
      top_elements = te.estimate
      top_elements.length.should == n_elemnts
      n_elemnts.times do |i|
        # check element
        top_elements[i][0].should == "test#{n_elemnts - i - 1}"
        # check weight
        exact_weight = convert_value_from_index(te_index, n_elemnts - i)
        top_elements[i][1].should == exact_weight
      end
    end

    it "return approximate number when the number of elements is greater than top_elems" do
      te = top_estimator.new(10)
      n_large_elemnts = 30
      n_small_elemnts = 1000
      # create input stream
      elems = []
      # large element x_i occurs x_i^2 times.
      n_large_elemnts.times do |i|
        (i * i).times do 
          elems << i
        end
      end
      # small element y_i occurs less than 5 times.
      n_small_elemnts.times do |i|
        rand(5).times do 
          elems << i
        end
      end
      # run input stream 2 times in random oreder
      2.times do 
        elems.sort_by{ rand }.each do |j|
          te.add_elem("test#{j}")
        end
      end
      # check estimation
      top_elements = te.estimate
      top_elements.length.should == 10
      10.times do |i|
        exact_index = n_large_elemnts - i - 1
        # check element
        top_elements[i][0] =~ /test(\d*)/
        estimated_index = $1.to_i
        diff = (exact_index - estimated_index).abs
        diff.should < 3
        # check weight
        exact_weight = convert_value_from_index(te_index, 2 * exact_index * exact_index)
        diff = top_elements[i][1] - exact_weight
        error = (diff / exact_weight.to_f).abs
        error.should < 0.1
      end
    end
    
  end
end
