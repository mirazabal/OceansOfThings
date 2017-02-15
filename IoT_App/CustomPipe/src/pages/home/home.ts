import { Component } from '@angular/core';

import { NavController } from 'ionic-angular';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

	private user : any;

	constructor(public navCtrl: NavController) {
		this.user = {
			name: 'Idioa Mendia',
			birthyear: 1886
		}
	}

}
