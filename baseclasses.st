Object subclass: #Object
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Object class methods !
new
	"создать новый объект нулевой длины, класса self"

	^self new: 0.!
new: anInteger
	"создать новый объект длины anInteger, класса self"

	^(<primitive: 11> value: anInteger value: self) class: self.!
printString
	^self name.
! !

!Object methods !
= anObject
	"сравниваются внутренности объектов (class, size, data[])"
	"^self hash = anObject hash. (ANSI)"
	"^self == anObject. (Squeak)"
	"note: подклассы его перекрывают"

	^<primitive: 21> value: self value: anObject value: true value: false.!
== anObject
	"сравнение по номерам, будет true если anObject и self это один и тот-же объект т.е. (self == self) -> true"
	"self identityHash = anObject identityHash (ANSI)"

	^<primitive: 10> value: self value: anObject value: true value: false.!
~= anObject
	"внутриности разные"

	^(self = anObject) not.!
~~ anObject
	"номера объектов разные"

	^(self == anObject) not.!
class
	"возвращает класс объекта"

	^<primitive: 15> value: self.!
doesNotUnderstand: aSymbol
	"если объект не может ответить на посланное сообщение вызывается этот метод (вызывает его VM)"

	^nil.!
error: aString
	"сообщить об ошибке"
	"^Error signal: aString. (ANSI)"

	^nil.!
isMemberOf: aClass
	"являемся ли мы экземпляром класса aClass (напр.: aClass new = self)"

	^self class == aClass.!
isKindOf: aClass
	"являемся ли мы экземпляром класса aClass или любого из его подклассов"

	^false.!
respondsTo: aSymbol
	"можем ли мы ответить на сообщение aSymbol"

	^self class canUnderstand: aSymbol.!
yourself
	"возвращаем себя-же (его незачем перекрывать в подклассах)"

	^self.!
printString
	"возвращает строку где сказано кто мы (в данном случае мы просто объект)"

	'an Object'.!
basicAt: anInteger
	"считать 1 байт, или вернуть nil"

	^<primitive: 19> value: self value: anInteger value: SmallInteger value: nil. !
basicAt: anInteger put: aObject
	"записать 1 байт, если указанна позиция больше длины self ничего не произойдет (self не изменится)"

	^<primitive: 20> value: self value: anInteger value: (anObject basicAt: 1).!
basicSize
	"возвращает размер объекта в байтах (без заголовка)"

	^<primitive: 13> value: self value: Integer.!
basicPut: anObject startAt: anInteger
	"начиная с позиции anInteger записываем все данные которые влезут из anObject"
	"(напр.: 'Smalltalk' basicPut: 'Talks' startAt: 6. -> 'SmallTalk')"

	^<primitive: 20> value: self value: anInteger value: anObject.!
at: anInteger
	"возвращает объект в позиции anInteger, если позиция указанна некоректно вернет nil"

	^<primitive: 22> value: self value: anInteger value: nil.!
at: anInteger put: anObject
	"записать объект anObject в позицию anInteger, если позиция указанна неверно то вернуть nil"

	^<primitive: 23> value: self value: anInteger value: anObject value: nil.!
size
	"возвращает количество объектов"

	^(<primitive: 13> value: self value: Integer) / 4.!
basicResize: anInteger
	"изменить размер на новый anInteger, если неудалось то вернем nil"

	^<primitive: 14> value: self value: anInteger value: nil.!
class: anObject
	"изменить класс к котораму мы принадлежим"

	^<primitive: 16> value: self value: anObject.!
flags
	"возвращает поле flags в заголовке объекта"

	^<primitive: 17> value: self value: Integer.!
flags: anInteger
	"меняет значение поля flags в заголовке объекта"

	^<primitive: 18> value: self value: anInteger.!
runGC
	"Запустить сборщик мусора (Garbage Collector) и собрать весь мусор"

	^<primitive: 12> value: self.!
isNil
	"мы не являемся nil"

	^false.!
notNil
	"да, все правельно, мы не являемся nil"

	^true.!
ifNil: aBlock
	"мы не будем выполнять aBlock т.к. мы не nil"

	^self.!
ifNotNil: aBlock
	"мы не nil и поэтому выполняем aBlock"

	^aBlock value.!
ifNil: aBlock1 ifNotNil: aBlock2
	"мы не nil и поэтому выполняем aBlock2"

	aBlock2 value.!
ifNotNil: aBlock1 ifNil: aBlock2
	"мы не nil и поэтому выполняем aBlock1"

	aBlock1 value.!
value
	"возвращаем наше значение (наше значение это мы)"

	^self.!
asPointer
	"возращаем указатель на себя (за одно становимся 'несдвигаемыми')"

	^<primitive: 32> value: self value: Pointer.!
printString
	"кто мы в виде строки"

	^'an Object'.!
shouldBeImplemented
	"Сообщить что этот метод будет сделан позже"

	self error: 'This method should be implemented.'.
! !

Object subclass: #Boolean
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Boolean methods !
xor: aBoolean
	"отрицание И"

	^(self = aBoolean) not.!
eqv: aBoolean
	"эквиволентность, равенство"

	^self == aBoolean.
! !

Boolean subclass: #False
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!False class methods!
new: anInteger
	"зачем создавать то что и так уже есть, тем более определенной длины"

	^false.
! !

!False methods !
& aObject
	"логическое И"

	^self.!
| aObject
	"логическое ИЛИ"

	^aObject.!
not
	"инверсия нас, НЕ"

	^true.!
and: aBlock
	"логическое И, но с результатом блока"

	^self.!
or: aBlock
	"логическое ИЛИ"

	^aBlock value.!
ifFalse: aBlock
	"если мы false (а мы false) то выполнить блок"

	^aBlock value.!
ifTrue: aBlock
	"если мы true (а мы не true) то выполнить блок"

	^nil.!
ifFalse: aBlock1 ifTrue: aBlock2
	"мы false и поэтому выбираем aBlock1 и выполняем его"

	^aBlock1 value.!
ifTrue: aBlock1 ifFalse: aBlock2
	"мы false и поэтому выбираем aBlock2 и выполняем его"

	^aBlock2 value.!
printString
	"кто мы"

	^'false'.
! !

Boolean subclass: #True
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!True class methods!
new: anInteger
	"зачем создавать то что и так уже есть, тем более определенной длины"

	^true.
! !

!True methods !
& aObject
	"логическое И"

	^aObject.!
| aObject
	"логическое ИЛИ"

	^self.!
not
	"инверсия нас, НЕ"

	^false.!
and: aBlock
	"логическое И, но с результатом блока"

	^aBlock value.!
or: aBlock
	"логическое ИЛИ, но с результатом блока"

	^self.!
ifFalse: aBlock
	"если мы false (а мы не false) то выполняем aBlock"

	^nil.!
ifTrue: aBlock
	"если мы true (а мы true) то выполняем aBlock"

	^aBlock value.!
ifFalse: aBlock1 ifTrue: aBlock2
	"если мы false то выполняем aBlock1, если true то aBlock2 (мы true)"

	^aBlock2 value.!
ifTrue: aBlock1 ifFalse: aBlock2
	"если мы true то выполняем aBlock1, если false то aBlock2 (мы true)"

	^aBlock1 value.!
printString
	"кто мы"

	^'true'.
! !

Object subclass: #UndefinedObject
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!UndefinedObject methods !
isNil
	"да мы nil"

	^true.!
notNil
	"нет мы nil"

	^false.!
ifNil: aBlock
	"если мы nil тогда выполняем aBlock"

	aBlock value.!
ifNotNil: aBlock
	"мы nil поэтому aBlock невыполняем"

	^self.!
ifNil: aBlock1 ifNotNil: aBlock2
	"поскольку мы nil то выполняем aBlock1"

	aBlock1 value.!
ifNotNil: aBlock1 ifNil: aBlock2
	"поскольку мы nil то выполняем aBlock2"

	aBlock2 value.!
printString
	"возвращает строковое предстовление себя"

	^'nil'.
! !

Object subclass: #Behavior
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

Behavior subclass: #ClassDescription
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!ClassDescription methods!
allSubclasses
	"возвращяем все подклассы текущего класса (все классы вниз по ирархии до конца)"

	self shouldBeImplemented.!
allSuperclasses.
	"возвращяем все суперклассы текущего класса (классы вверх по ирархии до Object)"

	self shouldBeImplemented.!
subclasses
	self shouldBeImplemented.!
superclasses
	self shouldBeImplemented.
! !

ClassDescription subclass: #Class
  instanceVariableNames: 'name superclass methods instCount'
  classVariableNames: ''
  poolDictionaries: ''    !

!Class methods!
name
	"название класса"

	^name.
! !

ClassDescription subclass: #MetaClass
  instanceVariableNames: 'name superclass methods instCount'
  classVariableNames: ''
  poolDictionaries: ''    !

!MetaClass methods!
name
	"название класса"

	^name.
! !

Behavior subclass: #Block
  instanceVariableNames: 'bytecode literals argCount tmpCount inTheClass name'
  classVariableNames: ''
  poolDictionaries: ''    !

!Block methods!
argumentCount
	"возвращает количество аргументов"

	^argCount!
repeat
	"бесконечно посылаем самому себе value, пока внутри не сработает возврат из метода"
	"[Time now minute == 0 ifTrue:[^'пииик']] repeat. ('пикнет' когда настанет новый час и прервет свой рекурсивный вызов)"

	self value.
	^self repeat.!
whileFalse: aBlock
	"выполняем aBlock пока результат нашего выполнения равен false"

	 ^self value
	     ifFalse:
		[aBlock value.
		[self value] whileFalse: aBlock].!
whileTrue: aBlock
	"выполняем aBlock пока результат нашего выполнения равен true"

	^self value
	     ifTrue:
		[aBlock value.
		[self value] whileTrue: aBlock].!
whileFalse
	"выполняем себя пока результат нашего выполнения равен false"

	^self whileFalse: [nil].!
whileTrue
	"выполняем себя пока результат нашего выполнения равен true"

	^self whileTrue: [nil].!
printString
	^'a BlockClosure'.
! !

Object subclass: #Magnitude
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Magnitude class methods!
new: anInteger
	"это абстрактный класс, он только для наследования"

	^nil.
! !

!Magnitude methods!
< aMagnitude
	"больше ли величена aMagnitude чем мы"
	
	^self subclassResponsibility.!
<= aMagnitude
	"больше или ровна ли величена aMagnitude чем мы"

	^(self > aMagnitude) not.!
> aMagnitude
	"меньше ли величена aMagnitude чем мы"

	^aMagnitude < self.!
>= aMagnitude
	"меньше или ровна величена aMagnitude чем мы"

	^(self < aMagnitude) not.!
between: aMinimumMagnitude and: aMaximumMagnitude
	"попадаем ли мы в указанный диапазон велечин, включительно"

	^self >= aMinimumMagnitude and: [self <= aMaximumMagnitude].!
max: aMagnitude
	"возвращаем наибольшую велечину из нас и aMagnitude"

	self > aMagnitude
		ifTrue: [^self]
		ifFalse: [^aMagnitude].!
min: aMagnitude
	"возвращаем наименьшую велечину из нас и aMagnitude"

	self < aMagnitude
		ifTrue: [^self]
		ifFalse: [^aMagnitude].
! !

Magnitude subclass: #Character
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Character class methods!
value: aInteger
	"создается буква соответствующая кодовой точке aInteger"
	"(используем однобайтовую кодировку)"
	
	^(super new: 4) basicAt: 1 put: aInteger.!
! !

!Character methods!
= aCharacter
	"сравниваем символы"

	^self == aCharacter or: [self codePoint = aCharacter codePoint].!
codePoint
	"вернем кодовую точку юникода т.е. числовое предстовление числа (поддерживаются только <128 символы)"

	^self at: 1.!
asLowercase
	^self.!
asString
	^' ' copy at: 1 put: self.!
asUppercase
	^self.!
isAlphaNumeric
	"являемся ли мы цифрой или буквой"

	^self notAlphaNumeric not.!
isDigit
	"являемся ли мы буквеным предстовлением цифры"

	^(self codePoint > 47) & (self codePoint < 58).!
isLetter
	"являемся ли мы буквой"

	^(self notAlphaNumeric not) & (self isDigit not).!
isLowercase	

	^true.!
isUppercase
	^true.!
notAlphaNumeric
	"этот символ не является не буквой не цифрой"
	
	| codepoint |
	codepoint := self codePoint.
	codepoint < 128
		ifTrue: [^(codepoint < 48) | ((codepoint > 57) & (codepoint < 65)) | ((codepoint > 90) & (codepoint < 97)) | (codepoint > 122)]
		ifFalse: [^true].
! !

Magnitude subclass: #Number
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Number methods!
* aNumber
	"умнажение двух чисел"

	^self subclassResponsibility.!
+ aNumber
	"сложение двух чисел"

	^self subclassResponsibility.!
- aNumber
	"вычитание чисел"

	^self subclassResponsibility.!
/ aNumber
	"деление чисел"

	^nil.!
// aNumber
	"два правых слеша"

	^nil.!
= aNumber
	"равенство двух чисел"

	^self subclassResponsibility.!
\\ aNumber
	"два левых слеша"
	
	^nil.!
quo: aNumber
	"целая часть от деления на aNumber (со знаком)"

	^(self / aNumber) truncated.!
rem: aNumber
	"дробная часть от деления на aNumber (со знаком)"

	^self - ((self quo: aNumber) * aNumber).!
negated
	"инверсия числа"

	^0 - self.!
abs
	"абсолютное значение числа"

	self < 0
		ifTrue: [^self negated]
		ifFalse: [^self].!
sign
	"знак числа (-1 0 1)"

	self > 0 ifTrue: [^1].
	self < 0 ifTrue: [^-1].
	^0.!
truncated
	"округляет число в меньшую сторону (???)"

	^self quo: 1.!
rounded
	"округление"
	
	^(self + (self sign / 2)) truncated.!
to: aStopNumber
	"интервал до aStopNumber числа"

	^Interval from: self to: aStopNumber by: 1.!
to: aStopNumber by: aStepNumber
	"интервал до aStopNumber числа с шагом aStepNumber"

	^Interval from: self to: aStopNumber by: StepNumber.!
to: aStopNumber by: aStepNumber do: aBlock
	"интервал до aStopNumber числа с шагом aStepNumber и пропустить через aBlock (блок с 1 аргументом)"

	^(Interval from: self to: aStopNumber by: StepNumber) do: aBlock.!
to: aStopNumber do: aBlock
	"интервал до aStopNumber числа с шагом 1 и пропустить через aBlock (блок с 1 аргументом)"

	^(Interval from: self to: aStopNumber by: 1) do: aBlock.
! !

Number subclass: #Integer
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Integer methods!
+ anInteger
	^<primitive: 65> value: self value: anInteger value: Integer value: nil.!
- anInteger
	^<primitive: 66> value: self value: anInteger value: Integer value: nil.!
* anInteger
	^<primitive: 67> value: self value: anInteger value: Integer value: nil.!
< anInteger
	^<primitive: 76> value: self value: anInteger value: true value: false.!
= anInteger
	^<primitive: 80> value: self value: anInteger value: true value: false.!
~= anInteger
	^(self = anInteger) not.!
/ anInteger
	"это простое деление должно по теории генерировать дробь - Fraction"
	^<primitive: 68> value: self value: anInteger value: Fraction.!
!

Number subclass: #Fraction
  instanceVariableNames: 'numerator denominator'
  classVariableNames: ''
  poolDictionaries: '' !

!Fraction class methods!
numerator: aNumber1 denominator: aNumber2
	"создать дробь из знаменателя и делителя"
	
	| newFraction |
	newFraction := super new: 8.
	newFraction at: 1 put: aNumber1.
	newFraction at: 2 put: aNumber2.
	^newFraction.!
!

!Fraction methods!
denominator
	^denominator.!
numerator
	^numerator.!
!


Object subclass: #Collection
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Collection class methods!
with: anObject
	"создать колекцию с одним объектом anObject"
	
	| newCollection |
	newCollection := self new.
	newCollection add: anObject.
	^newCollection.!
with: anObject1 with: anObject2
	"создать колекцию с двумя объектами anObject"
	
	| newCollection |
	newCollection := self new.
	newCollection add: anObject1.
	newCollection add: anObject2.
	^newCollection.!
with: anObject1 with: anObject2 with: anObject3
	"создать колекцию с тремя объектами anObject"
	
	| newCollection |
	newCollection := self new.
	newCollection add: anObject1.
	newCollection add: anObject2.
	newCollection add: anObject3.
	^newCollection.!
with: anObject1 with: anObject2 with: anObject3 with: anObject4
	"создать колекцию с четырмя объектами anObject"
	
	| newCollection |
	newCollection := self new.
	newCollection add: anObject1.
	newCollection add: anObject2.
	newCollection add: anObject3.
	newCollection add: anObject4.
	^newCollection.!
withAll: aCollection
	"создать коллекцию со всеми элементами из коллекции aCollection"

	| newCollection |
	newCollection := self new.
	aCollection do: [:element | newCollection add: element].
	^newCollection.!
!

!Collection methods!
add: anObject
	"добавить элемент в коллекцию"
	
	self subclassResponsibility.!
do: aBlock
	"выполнить aBlock с каждым элементом коллекции, передав этот элемент в виде аргумента aBlock"

	self subclassResponsibility.!
remove: anObject ifAbsent: aBlock
	"удалить равный (=) anObject из коллекции и если такого нет выполнить aBlock"

	self subclassResponsibility.!
do: aBlock separatedBy: aSeparatorBlock
	"пропустить все элементы через aBlock, но между элементами выполнить aSeporatorBlock"

	| isFirst |
	isFirst := true;
	self do: [:element | 
			isFirst 
				ifTrue: [isFirst := false]
				ifFalse: [aSeparatorBlock value]
			aBlock value: element.].!
detect: aBlock ifNone: exceptionBlock
	"ищет и возвращает первый элемент уловлетворяющий aBlock, если неудалось найти такой то выполняется exceptionBlock"

	self do: [:element | (aBlock value: each) ifTrue: [^element]].
	^exceptionBlock value.!
detect: aBlock
	"ищет и возвращает первый элемент уловлетворяющий aBlock"

	self detect: aBlock ifNone: [self errorNotFound: aBlock].!
collect: aBlock
	"прогоняет все элементы через aBlock и результаты складывает в новую коллекцию, которую потом возвращает"

	| newCollection |
	newCollection := self class new.
	self do: [:element | newCollection add: (aBlock value: element)].
	^newCollection.!
select: aBlock
	"возвращает колекцию из тех элементов относительно которых aBlock вернул true"
	
	| newCollection |
	newCollection := self class new.
	self do: [:element | (aBlock value: element) ifTrue: [newCollection add: element]].
	^newCollection.!
reject: aBlock
	"возвращает коллекцию из тех элементов про которые aBlock вернул false"

	^self collect: [:element | (aBlock value: element) == false].!
inject: startObject into: aBinaryBlock
	"все элементы коллекции пропустить через aBinaryBlock с результатом выполнения предыдущего вызова aBinaryBlock 
	(для первого вызова использовать startObject как результат)"
	
	| result |
	result := startObject.
	self do: [:element | result := aBinaryBlock value: result value: element].
	^result.!
includes: anObject
	"есть ли элемент колекции равный (=) anObject"

	self do: [:element | (element = anObject) ifTrue: [^true]].
	^false.!
occurrencesOf: anObject
	"сколько элементов в колекции равных (=) anObject"
	
	| count |
	count := 0.
	self do: [:element | (anObject = element) ifTrue: [count := count + 1]].
	^count.!
size
	"считает и возвращает количество элементов в коллекции"	

	| oursize |
	oursize = 0;
	self do: [:element | oursize := oursize + 1].
	^oursize.!
isEmpty
	"пустая ли коллекция"

	^self size = 0.!
notEmpty
	"есть ли элементы в коллекции"
	
	^self isEmpty not.!
allSatisfy: aBlock
	"все ли элементы коллекции удовлетворяют условию в aBlock"

	self do: [:element | (aBlock value: element) ifFalse: [^false]].
	^true.!
anySatisfy: aBlock
	"хоть один элемент удовлетворяет условию в aBlock"
	
	self do: [:element | (aBlock value: element) ifTrue: [^true]].
	^false.!
addAll: aCollection
	"добавить все элементи из коллекции aCollection в нас"

	aCollection do: [:element | self add: element].
	^aCollection.!
remove: anObject
	"удалить равный (=) anObject из коллекции"

	self remove: anObject ifAbsent: [self halt].
	^anObject.!
removeAll: aCollection
	"удалить все такие-же (=) элементы которые перечисленны в aCollection (по одному)"

	aCollection do: [:element | self remove: element].
	^aCollection.
! !

Collection subclass: #SequenceableCollection
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!SequenceableCollection methods!
do: aBlock
	"пропустить все элементы коллекции через aBlock"

	| start stop |
	start := 1.
	stop := self size.
	[start <= stop] 
		whileTrue: [
			aBlock value: (self at: start).
			start := start + 1.].!
= aSequenceableCollection
	"равны ли колекции"

	| start stop |
	(self class == aSequenceableCollection class) ifFalse: [^false].
	(self size = aSequenceableCollection size) ifFalse: [^false].
	start := 1.
	stop := self size.
	[start <= stop]
		whileTrue: [
			(self at: start) = (aSequenceableCollection at: start)
				ifFalse: [^false].
			start := start + 1.
			]
	^true.!
at: anInteger ifAbsent: aBlock
	"вернуть объект лежащий в позиции anInteger, иначе выполнить aBlock"

	(anInteger between: 1 and: self size) ifFalse: [aBlock value].
	^super at: anInteger.!
!



Collection subclass: #Set
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

Set subclass: #Dictionary
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

Dictionary subclass: #CompactDictionary
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!CompactDictionary methods!
at: aKey
	| result |
	"Поиск aKey в словаре Smalltalk если не найдено то вернет себя-же (вообще надо бросать Exception)"

	^<primitive: 126> value: self value: aKey value: self.
! !

SequenceableCollection subclass: #ArrayedCollection
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

ArrayedCollection subclass: #String
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!String methods!
asString
	^self.!
size
	^self basicSize / 2.!
at: aNumber ifAbsent: aBlock
	self size < aNumber 
		ifTrue:[^aBlock value].
		ifFalse: [^Character value: ((self basicAt: aNumber * 2) * 256) + (self basicAt: aNumber * 2 + 1)].!
atByteOffset: aNumber
	"Возвращает символ (Character) по указанному смищению в байтах"	

	| firstbyte |

	firstbyte := self basicAt: aNumber.
	firstbyte < 128
		ifTrue: [^Character utf8value: firstbyte].
	
	firstbyte < 224
		ifTrue: [^Character utf8value: firstbyte * 256 + (self basicAt: aNumber+1)].

	firstbyte < 240
		ifTrue: [^Character utf8value: firstbyte * 65536 + ((self basicAt: aNumber+1) * 256) + (self basicAt: aNumber+2)].

	^Character utf8value: firstbyte * 16777216 + ((self basicAt: aNumber+1) * 65536) + ((self basicAt: aNumber+2) * 256) + (self basicAt: aNumber+3).!
indexToByteOffset: aNumber
	"определяет смещение в байтах для указанного порядкового номера символа"

	| currentOffset sizeInByte byte |
	currentOffset := 1.
	sizeInByte = self basicSize.
	
	[aNumber = 0] whileFalse: [
		byte := self basicAt: currentOffset.
		byte < 128
			ifTrue: [currentOffset := currentOffset+1].
			ifFalse: [byte < 224
				ifTrue: [currentOffset := currentOffset+2]
				ifFalse: [byte < 240
					ifTrue:[currentOffset := currentOffset+3]
					ifFalse: [currentOffset := currentOffset+4]]].
		aNumber := aNumber - 1.] 

	^currentOffset.
! !

String subclass: #Symbol
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !






Object subclass: #Transcript
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Transcript class methods!
nl
	"пропуск строки"
	
	^<primitive: 112> value: ''.!
showCr: aString
	"вывести aString в поток out"
	
	^<primitive: 112> value: aString.
! !


Object subclass: #TestsForBaseClasses
  instanceVariableNames: ''
  classVariableNames: 'savedContextState savedblock savedblocks '
  poolDictionaries: ''    !

!TestsForBaseClasses class methods!
startTesting
	Transcript showCr: 'Start testing base classes ...'.
	Transcript nl.

	Transcript showCr: 'testing SimpleTests...'.
	self startSimpleTests.
	Transcript nl.

	Transcript showCr: 'testing BlockClosure...'.
	self startTestingBlocks.

	^nil.
!
startSimpleTests 
	| obj1 obj2 |
	Transcript showCr: nil printString.
	Transcript showCr: true printString.
	Transcript showCr: false printString.
	Transcript showCr: (self = self) printString.
	Transcript showCr: (self == self) printString.
	Transcript showCr: (self = 1) printString.
	Transcript showCr: (true = false) printString.
	Transcript showCr: (true == false) printString.
	Transcript showCr: (true = true) printString.
	Transcript showCr: (1 = 1) printString.
	Transcript showCr: (1 == 1) printString.
	Transcript showCr: (1 = 2) printString.
	Transcript showCr: ('123' = '123') printString.
	Transcript showCr: ('123' == '123') printString.
	Transcript showCr: Object printString.
	Transcript showCr: Object new printString.
	Transcript showCr: ((Object new: 1) basicAt: 1 put: 56);

!
startTestingBlocks
	Transcript showCr: [1] printString.
	Transcript showCr: ['123'] value.
	Transcript showCr: self testBlock1.
	Transcript showCr: (true ifTrue: ['ifTrue']).
	Transcript showCr: (true ifFalse: ['ifFalse']) printString.
	Transcript showCr: (true ifTrue: ['ifTrue'] ifFalse: ['ifFalse']) printString.
	Transcript showCr: (nil ifNil: ['ifNil']).
	Transcript showCr: (nil ifNil: ['ifNil'] ifNotNil: ['ifNotNil']).
!
testBlock1
	[^'321'] value.
! !