def function_p(x)
  (x*x - 5*x + 6) == 0
end

def function_q(x)
  (x*x - 4*x - 5) == 0
end

def function_r(x)
  x > 0
end

(-10_000..10_000).each do |i|
  a = function_p(i)
  b = function_r(i)

  if a == false && b == false
    puts i
  end
end

