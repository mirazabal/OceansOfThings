import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { UserService } from '../../services/user';
import { Page2 } from '../page2/page2';


/*
  Generated class for the Page1 page.

  See http://ionicframework.com/docs/v2/components/#navigation for more info on
  Ionic pages and navigation.
*/
@Component({
  selector: 'page-page1',
  templateUrl: 'page1.html'
})
export class Page1 {

	private user: any;
	private nav: any;

  constructor(public navCtrl: NavController, user: UserService, nav: NavController) {
	console.log(user.name);
	this.user = user;
	this.nav = nav;
  }

  goToPage2() {
	this.nav.push(Page2);
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad Page1Page');
  }

}
