require "szaru"

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


def test_topheap
  th = SZaru::TopHeap.new(3)
  th.add_new_elem("test", 45.0)
  th.add_new_elem("test1", 3.0)
  th.add_new_elem("test2", 2.4)
  th.add_new_elem("test3", 4.0)
  th.add_new_elem("test4", 9.1)
  p th.smallest
end

def test_sketch
  sketch = SZaru::Sketch.new(10 * 100)
end

def test_top
  te = SZaru::TopEstimator.new(10)
  ary = []
  1000.times do |i|
    i.times do |j|
      ary << "test#{i}"
    end
  end
  ary.sort_by{rand}.each do |e|
    te.add_elem(e)
  end
  p te.estimate
end

def test_quantile
  te = SZaru::Int64QuantileEstimator.new(10)
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
# test_top
test_quantile
