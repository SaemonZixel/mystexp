Object subclass: #MySTCompiler
	| meAsPointer |
	meAsPointer := <primitive: 32> value: self.
	meAsPointer isMagnitude ifTrue: [meAsPointer class: Pointer].
	^meAsPointer.!!
'.