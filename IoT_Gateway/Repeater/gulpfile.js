var gulp = require('gulp');
var mocha = require('gulp-mocha');

gulp.task('test', function() {
  var error = false;
	console.log("qwe");
   gulp.
    src('./test.js').
    pipe(mocha()).
    on('error', function() {
		console.log("Test really failed");
  		console.log('Tests failed!');
      error = true;
    }).
    on('end', function() {
      if (!error) {
        console.log('Tests succeeded! Enter the below code:\n' +
          require('fs').readFileSync('./output.dat'));
        process.exit(0);
      }
    });
});

gulp.task('watch', function() {
  gulp.watch(['./index.js', 'models.js' , 'client-pub.js' , 'client-sub.js' , 'dependencies.js', 'mosca-app.js', 'test.js', 'gulpfile.js'  ], ['test']);
  });