<?php 
/**
 * Theme Individual Object Page
 */

if (isset($_GET['dpm-record'])) {
  dpm($variables);
}

?>




 <div class="wrapper-edan-object bg-none<?php print $show_backLink ? ' showLink' : ''; ?>">
   <?php if ($unit_link): ?>
     <div class="bg-gray-light bg wrapper--si-unit">
       <div class="inside l-container">

         <div class="<?php echo $unit_class;?>">
           <?php echo $unit_link; ?></div>
       </div>

   </div>
     <?php endif; ?>


     <div class="wrapper--preface-buttons">
       <div class="l-container link-wrapper">
         <?php if($back_link): 		?>
           <div class="back-link"><?php echo $back_link; ?></div>
         <?php endif; ?>
           <?php
           $block = module_invoke('addthis', 'block_view', 'addthis_block');
           echo render($block['content']);
           ?>
       </div>
    </div>



     <?php foreach ($docs as $i => $doc): ?>
       <?php if($doc['type'] !== 'edanead'): ?>
         <div class="edan-content">
           <div class="l-container pane-page-header">
             <h2 class="pane-title alpha"><?php echo isset($doc['#title_plain']) ? t($doc['#title_plain']) : $doc['#title']; ?></h2>
           </div>

           <div <?php echo drupal_attributes($doc['row_attributes']); ?>>


             <?php if (isset($_GET['dump'])): ?>
               <?php echo '<pre>' . var_export($doc, TRUE) . '</pre>';
             else: ?>


               <?php if ($doc['rendered_media']): ?>
                 <div class="record-media">
                   <?php echo $doc['rendered_media']; ?>
                 </div>
               <?php endif; ?>
               <div class="record-details">
                 <?php foreach ($doc['content']['freetext'] as $field => $vals): ?>
                   <dl class="edan-search-<?php echo $field; ?>">
                     <?php $current_label = ''; ?>
                     <?php foreach ($vals as $value): ?>
                       <?php if ($value['label'] != $current_label): ?>
                         <dt><?php echo $value['label']; ?></dt><?php $current_label = $value['label']; ?>
                       <?php endif; ?>
                       <dd><?php echo $value['content']; ?></dd>
                     <?php endforeach; ?>
                   </dl>
                 <?php endforeach; ?>
               </div>
             <?php endif; ?>


           </div>
           <?php endif; ?>
           <?php endforeach; ?>


   <?php
   $block = module_invoke('ogmt', 'block_view', 'related_objectgroups');
   if(isset($block['content'])):?>
   <div class="wrapper--related-ogmt l-container">
     <div class="group-header">
       <div class="header-theme"></div>
       <h2 class="pane-title"><?php echo $block['subject']?></h2>
     </div>
     <?php echo render($block['content']); ?>
   </div>
   <?php endif; ?>
         </div>


 </div>

  

    
   

  

