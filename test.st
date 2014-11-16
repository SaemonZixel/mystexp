Object subclass: #Object
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Object class methods !
new

	^<primitive: 11> value: 0.!
new: aSize
	^<primitive: 11> value: aSize.!
! !

!Object methods !
basicAt: aNumber
	^<primitive: 19> value: self value: aNumber. !
at: aNumber
	^<primitive: 22> value: self value: aNumber.!
basicAt: aNumber put: aObject
	^<primitive: 20> value: self value: aNumber value: (aObject basicAt: 1).!
at: aNumber put: aObject
	^<primitive: 23> value: self value: aNumber value: aObject.!
basicSize
	^<primitive: 13> value: self.!
size
	^<primitive: 13> value: self.!
basicResize: aNumber
	^<primitive: 14> value: self value: aNumber.!
class
	^<primitive: 15> value: self.!
class: aNumber
	^<primitive: 16> value: self value: aNumber.!
formemmng
	^<primitive: 17> value: self.!
formemmng: aData
	^<primitive: 18> value: self value: aData.!
free
	^<primitive: 12> value: self.!
== aObject
	^<primitive: 21> value: self value: aObject.!
= aObject
	^<primitive: 10> value: self value: aObject.!
isNil
	^false.!
notNil
	^true.!
ifNil: aBlock
	^self.!
ifNotNil: aBlock
	^aBlock value.!
ifNil: aBlock1 ifNotNil: aBlock2
	aBlock2 value.!
ifNotNil: aBlock1 ifNil: aBlock2
	aBlock1 value.!
value
	^self.!
asPointer
	| meAsPointer |
	meAsPointer := <primitive: 32> value: self.
	meAsPointer isMagnitude ifTrue: [meAsPointer class: Pointer].
	^meAsPointer.!
isObject
	^true.!
isBlock
	^false.!
isMethod
	^false.!
isBehavior
	^false.!
isMessage
	^false.!
isCompiler
	^false.!
isContext
	^false.!
isUndefinedObject
	^false.!
isBoolean
	^false.!
isMagnitude
	^false.!
isCollection
	^false.!
isPointer
	^false.
! !

Object subclass: #Boolean
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!Boolean methods !
xor: aBoolean
	^(self = aBoolean) not.!
isBoolean
	^true.!
isTrue
	^false.!
isFalse
	^false.
! !

Boolean subclass: #False
  instanceVariableNames: ''
  classVariableNames: ''
  poolDictionaries: ''    !

!False methods !
& aObject
	^self.!
| aObject
	^aObject.!
not
	^true.!
and: aBlock
	^self.!
or: aBlock
	^aBlock value.!
ifFalse: aBlock
	^aBlock value.!
ifTrue: aBlock
	^nil.!
ifFalse: aBlock1 ifTrue: aBlock2
	^aBlock1 value.!
ifTrue: aBlock1 ifFalse: aBlock2
	^aBlock2 value.!
ifTrue: aBlock1 else: aBlock2
	^aBlock2 value.!
ifFalse: aBlock1 else: aBlock2
	aBlock1 value.!
isFalse
	^true.
! !
