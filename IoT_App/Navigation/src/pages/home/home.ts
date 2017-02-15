import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';

import { AboutPage } from '../about/about';


@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

public myString: string='Example 1-this is just a str';
public myJSON: any = {text: ''};
//otherPage: any = OtherPage;
aboutPage:any = AboutPage;


  constructor(public navCtrl: NavController) {

  }

	gotoOtherPage() {
		this.navCtrl.push(AboutPage, {text: 'Example 3 this is an object'} );
	
	}

}
