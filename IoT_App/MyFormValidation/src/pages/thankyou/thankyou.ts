import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { MyFormService } from '../../services/myform';

/*
  Generated class for the Thankyou page.

  See http://ionicframework.com/docs/v2/components/#navigation for more info on
  Ionic pages and navigation.
*/
@Component({
  selector: 'page-thankyou',
  templateUrl: 'thankyou.html'
})
export class ThankYouPage {

  constructor(private formData: MyFormService) {
		this.formData = formData;
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad ThankyouPage');
  }

}
