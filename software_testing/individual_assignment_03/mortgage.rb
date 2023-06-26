def mortgage male, age, salary
  if male
    return (18 <= age and age < 35) ? (75 * salary) : ((31 <= age and age < 40) ? (55 * salary) : (30 * salary))
  end

  return (18 <= age and age < 30) ? (75 * salary) : ((31 <= age and age < 40) ?  (50 * salary) : (35 * salary))
end


# gender
gender = nil
while gender == nil
  puts "Please input Gender: Male (M) or Female (F)"
  input = gets.chomp
  if input == 'M' or input == 'm' or input.to_s.downcase == 'male'
    gender = true
  elsif input == 'F' or input == 'f' or input.to_s.downcase == 'female'
    gender = false
  else
    puts "Wrong input. Please input M for Man or W for Woman"
  end
end

# age
age = 0
while age == 0
  puts "Please input age >= 18: "
  input = gets.chomp
  if input.to_i >= 18 and input.to_i <= 55
    age = input.to_i
    break
  end

  puts "Wrong input."
end

# input salary
salary = 0
while salary == 0
  puts "Please input salary (> 0): "
  input = gets.chomp
  if input.to_i >= 0 and input.to_i <= 10_000
    salary = input.to_i
    break
  end

  puts "Wrong input."
end

puts mortgage(gender, age, salary)


