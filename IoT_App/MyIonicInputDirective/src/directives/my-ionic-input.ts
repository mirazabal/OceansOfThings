import { Directive, ElementRef, Input} from '@angular/core';

@Directive({
	selector: '[myIonicInput]',
	host: {
		'(mouseenter)': 'onMouseEnter()',
		'(mouseleave)': 'onMouseLeave()'	
	}
})

export class MyIonicInputDirective{
@Input('myIonicInput') myStyles: any;

constructor(private el: ElementRef){
	el.nativeElement.onkeypress = function (e) {
		console.log(e);
		if( '~!@#$%&*()-='.includes(String.fromCharCode(e.keyCode) ) ){
			e.preventDefault();
			return;
		}
	}
}

onMouseEnter() {
	this.myStyles.showUsername = true;
}

onMouseLeave() {
	this.myStyles.showUsername = false;
}

}



