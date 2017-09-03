<?php //dpm($variables); ?>
<?php if(!empty($rows)): ?>
  <div class="grid-wrapper equal-col l-container search-results">
    <ul class="related-ogmt-block reset-list content">

      <?php foreach ($rows as $doc): ?>
        <li class="col col-sm-6 col-md-4 col-wd-3">
          <div class="<?php echo $doc['result_class'] ?>">
            <a href="<?php echo $doc['#record_link']?>" class="inner" target="_blank">
              <?php if($doc['rendered_image']): ?>
              <div class="b-media-wrapper field--type-image">
                <?php print $doc['rendered_image']; ?>
              </div>
              <?php endif; ?>

              <div class="b-text-wrapper">
                <h3 class="title">
                  <?php print $doc['list_title'];?>
                </h3>
              </div>
            </a>
          </div>

        </li>

      <?php endforeach; ?>
    </ul>
  </div>
<?php endif; ?>