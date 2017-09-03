<?php

if (module_exists('devel') && isset($_GET['dpm']) && user_access('access devel information')) {
  dpm($variables);
} elseif (isset($_GET['dump'])) {
  var_export($variables['docs']);
}
$query = array(
  'width' => '85%',
  'height' => '85%',
  'iframe' => 'true',
  'destination' => $destination
);
?>


  <!-- Slider main container -->
<div class="l-container-wide exhbition-block swiper-container-wrapper has-nav">
  <div class="swiper-container exhibitions-wrapper" id="<?php print $id; ?>">
    <!-- Additional required wrapper -->
      <ul class="reset-list swiper-wrapper content search-results exhbition-search">
        <?php foreach ($docs as $i => $doc):
          $doc['row_attributes']['class'][] = 'swiper-slide';
          ?>
          <li <?php echo drupal_attributes($doc['row_attributes']); ?>>
            <a href="<?php echo url($doc['#record_link'], array('query' => $query)); ?>"
               class="card card--exhibit colorbox-load">
              <?php if (isset($doc['rendered_image']) && !empty($doc['rendered_image'])): ?>
                <figure>
                  <?php echo $doc['rendered_image']; ?>
                </figure>
              <?php endif; ?>
              <div class="b-text-wrapper">
                <h3 class="name epsilon"><?php echo $doc['title']; ?></h3>
                <p class="metatag">
                  <span class="date"><?php echo $search_name === 'whats-on-closing' ? 'Closes '. $doc['content']['close']['content'] : ($search_name === 'whats-on-recent' ? 'Opened '. $doc['content']['open']['content'] : $doc['#short_date'])?></span>
                </p>
              </div>
            </a>
          </li>
        <?php endforeach; ?>
      </ul>

    <!-- If we need navigation buttons -->
    <div class="swiper-button-prev"></div>
    <div class="swiper-button-next"></div>
  </div>
</div>





