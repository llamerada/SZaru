require File.join(File.dirname(__FILE__), "../ext/szaru")

def test_unique
  ue = SZaru::UniqueEstimator.new(4)
  1000.times do |i|
    ue.add_elem(i.to_s + "test")
  end
  1000.times do |i|
    ue.add_elem(i.to_s + "hoge")
  end
  puts ue.estimate
end

def test_top
  te = SZaru::TopEstimator::Int32.new(10)
  ary = []
  100.times do |i|
    i.times do |j|
      ary << "test#{i}"
    end
  end
  ary.sort_by{rand}.each do |e|
    te.add_elem(e)
  end
  p te.estimate
end

def test_top2
  te = SZaru::TopEstimator::Double.new(10)
  ary = []
  100.times do |i|
    ary << ["test#{i}", i]
  end
  ary.sort_by{rand}.each do |e, w|
    te.add_weighted_elem(e, w.to_f)
  end
  p te.estimate
end

def test_quantile
  te = SZaru::QuantileEstimator::Int64.new(10)
  ary = []
  1000.times do |i|
    # i.times do |j|
    ary << i
  end
  rand_ary  = ary.sort_by{rand}
  # $stdout.sync = true
  # puts "start"
  rand_ary.each_with_index do |e, i|
    te.add_elem(e)
  end
  p te.estimate
end



# test_topheap
# test_sketch
test_unique
test_top
test_top2
test_quantile
